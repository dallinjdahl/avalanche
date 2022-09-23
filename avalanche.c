#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "param.h"
#include "avalanche.h"

#define HALF (1 << ((1 << (IN)) -1))

#define min(x, y) ((x) < (y) ? (x) : (y))
#define abs(x) (((signed) (x))< 0  ? -(x) : (x))


IN_T table[1 << IN][1 << OUT] = {0};

IN_T flip(IN_T x, uint8_t pos) {
	return x ^ (1 << pos);
}

void report(OUT_T x, OUT_T y, uint8_t pos) {
	x ^= y;
	uint8_t i = 0;
	while(x) {
		if(x&1) {
			table[i][pos]++;
		}
		x >>= 1;
		i++;
	}
}

void bigendian(uint32_t x, char *s) {
	uint8_t i = 4;
	while(i --> 0) {
		*s++ = x >> 24;
		x <<= 8;
	}
}

uint8_t weight(IN_T count) {
	IN_2T x = count;
	x -= HALF;
	x = abs(x);
	x = min(x, HALF-1);
	x *= 256;
	x /= HALF;
	return 255-x;
}
	

void scanline(uint8_t y) {
	static char pixel[8] = {0,0,0,0,0,0,0xff,0xff};
	uint32_t interim;
	uint8_t i = 1 << IN;
	while(i --> 0) {
		interim = table[y][i];
		pixel[2] = weight(interim);
		for(uint8_t j = 0; j < SCALE; j++) {
			write(1, pixel, 8);
		}
	}
}

void render() {
	static char header[16] = {'f', 'a', 'r', 'b', 'f', 'e', 'l', 'd'};
	uint8_t i = 1 << OUT;
	bigendian(SCALE << IN, header+8);
	bigendian(SCALE << OUT, header+12);
	write(1, header, 16);
	for(uint8_t i = 0; i < (1 << OUT); i++)
		for(uint8_t j = 0; j < SCALE; j++) {
			scanline(i);
		}
	}
}

void debug() {
	for(uint8_t i = 0; i < (1 << OUT); i++) {
		for(uint8_t j = 0; j < (1 << IN); j++) {
			fprintf(stderr, "%5d ", table[i][j]);
		}
		fprintf(stderr, "\n");
	}
}
	
void evaluate(OUT_T (*hash)(IN_T)) {
	IN_T initial = ~0, modify;
	OUT_T baseline, datum;
	uint8_t j;
	while(initial) {
		baseline = hash(initial);
		j = 1 << IN;
		while(j --> 0) {
			modify = flip(initial, j);
			datum = hash(modify);
			report(baseline, datum, j);
		}
		initial--;
	}
	render();
	//debug();
}
	

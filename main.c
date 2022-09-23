#include <stdint.h>
#include <stdlib.h>
#include "param.h"
#include "avalanche.h"

uint16_t hash(uint16_t x) {
	x *= 13;
	x ^= x >> 5;
	x *= 7;
	x ^= x >> 11;
	x *= 15;
	return x;
}

int main(int argc, char **argv) {
	evaluate(hash);
	return 0;
}

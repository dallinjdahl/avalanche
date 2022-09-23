#include <stdio.h>
#include "config.h"

int main(int argc, char **argv) {
	printf("#define IN %d\n#define OUT %d\n#define SCALE %d\n", IN, OUT, SCALE);
	printf("#define IN_T uint%d_t\n#define OUT_T uint%d_t\n", 1 << IN, 1 << OUT);
	printf("#define IN_2T uint%d_t\n#define OUT_2T uint%d_t\n", 2 << IN, 2 << OUT);
	return 0;
}


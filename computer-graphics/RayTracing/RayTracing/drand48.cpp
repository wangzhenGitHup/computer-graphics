#include "drand48.h"

double drand48(void)
{
	seed = (A * seed + C) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return 	((double)x / (double)M);

}

void srand48(unsigned int i)
{
	seed = (((long long int)i) << 16) | rand();
}
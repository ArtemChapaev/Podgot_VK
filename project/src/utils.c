#include "utils.h"

size_t timer_from(unsigned int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        if (i != 0) {
            putchar(' ');
        } else {
	    putchar('\n');
        }
    }
    return counter;
}

int custom_pow(int base, int power) {
    if (base == 1)
	return base;

    int result = 1;
    while (power != 0) {
	result *= base;
	power--;
    }
    return result;
}


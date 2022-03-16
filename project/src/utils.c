#include <stdio.h>
#include <stdlib.h>

int strtol_with_checking_err(const char* str, int* num) {
    char* end = NULL;
    *num = strtol(str, &end, 0);
    if (*end != '\0') {
	return 1;
    }
    return 0;
}

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


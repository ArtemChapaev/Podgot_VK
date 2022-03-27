#include <stdio.h>
#include <stdlib.h>

int strtol_with_checking_err(const char *str, int *num) {
    char *end = NULL;
    *num = strtol(str, &end, 0);
    if (*end != '\0') {
        return 1;
    }
    return 0;
}

size_t timer_from(unsigned int from) {
    int i;
    for (i = from; i >= 0; --i) {
        printf("%d", i);
        if (i != 0) {
            putchar(' ');
        }
    }

    if (i == -1) {
        putchar('\n');
        return ++from;
    } else {
        return 0;
    }
}

int custom_pow(int base, int power) {
    if (base == 1)
        return base;

    int result = 1;
    for (; power != 0; --power) {
        result *= base;
    }
    return result;
}


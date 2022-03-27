#include <stdlib.h>
#include <stdio.h>

int prime_number_validation(int num) {
    if (num < 2) {
        return 0;
    }
    if (num % 2 == 0) {
        return 0;
    }

    int i = 3;
    while (num > i * i) {
        if (num % i == 0) {
            return 0;
        } else {
            i += 2;
        }
    }
    return 1;
}

#include "some.h"

int prime_number_validation(int num) {
    if (num < 2) {
        return 0;
    }
    int i = 2;
    while (num > i) {
        if (num % i == 0) {
            return 0;
        } else {
            if (i == 2) {
                ++i;
            } else {
                i += 2;
            }
        }
    }
    return 1;
}

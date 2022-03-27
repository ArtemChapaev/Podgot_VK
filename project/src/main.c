#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "prime_number.h"
#include "numbers_to_one.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)
#define ERR_WRONG_ARG (-3)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_MOD_ENUM   4

int main(int argc, const char **argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int test_case;
    int return_code = strtol_with_checking_err(argv[1], &test_case);
    if (return_code != 0) {
        return ERR_WRONG_ARG;
    }

    const char *data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            int to;
            return_code = strtol_with_checking_err(data, &to);
            if (return_code != 0) {
                return ERR_WRONG_ARG;
            }
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc != 4) {
                return ERR_ARGS_COUNT;
            }

            int base;
            return_code = strtol_with_checking_err(data, &base);
            if (return_code != 0) {
                return ERR_WRONG_ARG;
            }

            int pow;
            return_code = strtol_with_checking_err(argv[3], &pow);
            if (return_code != 0) {
                return ERR_WRONG_ARG;
            }

            int res = custom_pow(base, pow);
            printf("%d\n", res);
            break;
        }
        case TST_MOD_IMPL: {
            int num;
            return_code = strtol_with_checking_err(data, &num);
            if (return_code != 0) {
                return ERR_WRONG_ARG;
            }

            int res = prime_number_validation(num);
            printf("%d\n", res);
            break;
        }
        case TST_MOD_ENUM: {
            int num;
            return_code = strtol_with_checking_err(data, &num);
            if (return_code != 0) {
                return ERR_WRONG_ARG;
            }

            numbers_to_one(num, 1);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}

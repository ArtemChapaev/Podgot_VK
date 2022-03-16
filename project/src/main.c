#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "prime_number.h"
#include "recursion.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)
#define ERR_WRONG_ARG (-3)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_MOD_CREAT   4

/* NOTE(stitaevskiy):
 * We use `atoi` function just for simplification and code reducing.
 * This function doesn't report conversation errors.
 * For safety program we recommend using `strtol` and its analogs.
 * (See `man atoi` and `man strtol` for more info).
 *
 * const char str_num[] = "1234";
 * char* end = NULL;
 * int val = (int) strtol(str_num, &end, 0);
 * if (end != '\0') {
 *     //ERROR
 * }
 *
 * */

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int Test_case;
    int return_code = strtol_with_checking_err(argv[1], &Test_case);
    if (return_code != 0) {
	return ERR_WRONG_ARG;
    }
    const char* data;
    data = argv[2];

    switch (Test_case) {
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
            if (argc == 4) {
                int base;
		return_code = strtol_with_checking_err(data, &base);
		if (return_code != 0) {
		     return ERR_WRONG_ARG;
		}
                int pow;
		return_code =  strtol_with_checking_err(argv[3], &pow);
                if (return_code != 0) {
		     return ERR_WRONG_ARG;
		}
		int res = custom_pow(base, pow);
                printf("%d\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
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
	case TST_MOD_CREAT: {
	    int num;
	    return_code = strtol_with_checking_err(data, &num);
	    if (return_code != 0) {
		return ERR_WRONG_ARG;
	    }
            numbers_to_one(num, 1);  // Вызов функции рекурсивного вывода чисел от 1 до num
	    break;
	}
        default: {
            return ERR_WRONG_FLG;
        }
    }
}

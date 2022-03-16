#include "some.h"

int strtol_with_checking_err(const char* str);

size_t timer_from(unsigned int from);

int custom_pow(int base, int power);

int prime_number_validation(int num);

void numbers_to_one(int num, int output_num);

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

    int Test_case = strtol_with_checking_err(argv[1]);
    const char* data;
    data = argv[2];

    switch (Test_case) {
        case TST_FOO_FIX: {
            int to = strtol_with_checking_err(data);
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                int base = strtol_with_checking_err(data);
                int pow =  strtol_with_checking_err(argv[3]);
                int res = custom_pow(base, pow);
                printf("%d\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
      	    break;
        }
        case TST_MOD_IMPL: {
            int num = strtol_with_checking_err(data);
	    int res = prime_number_validation(num);
	    printf("%d\n", res);
	    break;
        }
	case TST_MOD_CREAT: {
	    int num = strtol_with_checking_err(data);
            numbers_to_one(num, 1);  // Вызов функции рекурсивного вывода чисел от 1 до num
	    break;
	}
        default: {
            return ERR_WRONG_FLG;
        }
    }
}

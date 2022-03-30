#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_and_recording.h"
#include "tests.h"

#define ARRAY_SIZE(_a) (sizeof(_a) / sizeof((_a)[0]))

int full_test_file();

static unit_test u_tests[] = {
        test_write_file,
        test_read_file
};

int main() {
    int return_code = full_test_file();
    if (return_code != 0) {
        printf("%s", ERROR_MESSAGE);
        return ERR_WRONG_TEST;
    } else {
        printf(CORRECT_END_MESSAGE);
    }

    for (size_t i = 0; i < ARRAY_SIZE(u_tests); i++) {
        return_code = u_tests[i]();
        if (return_code != 0) {
            printf("%s", ERROR_MESSAGE);
            return return_code;
        } else {
            printf(CORRECT_END_MESSAGE);
        }
    }
    return 0;
}

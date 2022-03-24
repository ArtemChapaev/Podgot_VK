#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils_for_tests.h"
#include "utils.h"
#include "base_updating.h"

int test_read_file();

int main() {
    int return_code = test_read_file();

    if (return_code != 0) {
        printf(ERROR_MESSAGE);
    } else {
        printf(CORRECT_END_MESSAGE);
    }

    return return_code;
}

int test_read_file() {
    // пункт 1: чтение данных из файла
    data_t got_data;
    FILE *p_read_file = fopen(UNIT_TEST_FILE, "r");

    if (p_read_file == NULL) {
        return ERR_NO_FILE_OPENED;
    }

    int return_code = read_credentials_from_file(p_read_file, &got_data);
    if (return_code != 0) {
        return ERR_WRONG_READING_FROM_FILE;
    }
    fclose(p_read_file);

    // пункт 2: проверка правильности чтения
    if (got_data.number == 0 || got_data.indebtedness == 0 ||
        got_data.credit_limit == 0 || got_data.cash_payments == 0 ||
        got_data.name == NULL || got_data.surname == NULL ||
        got_data.address == NULL || got_data.tel_number == NULL) {
        return ERR_WRONG_COMPARING;
    }
    return 0;

}

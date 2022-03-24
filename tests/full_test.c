#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils_for_tests.h"
#include "utils.h"
#include "base_updating.h"
#include "credentials_recording.h"

int test_write_to_file();

int main() {
    int return_code = test_write_to_file();

    if (return_code != 0) {
        printf(ERROR_MESSAGE);
        return ERR_WRONG_TEST;
    }

    printf(CORRECT_END_MESSAGE);
    return 0;
}

int test_write_to_file() {
    // пункт 1: запись в файл
    data_t expected_data = {
            111, "Name_11", "Surname_11", "Moscow",
            "88005353535", 111, 111, 111};

    FILE *p_test_file = fopen(FULL_TEST_FILE, "w");

    if (p_test_file == NULL) {
        return ERR_NO_FILE_OPENED;
    }
    write_to_file_credentials(p_test_file, expected_data);
    fclose(p_test_file);

    // пункт 2: чтение данных из файла
    data_t got_data;
    p_test_file = fopen(FULL_TEST_FILE, "r");

    if (p_test_file == NULL) {
        return ERR_NO_FILE_OPENED;
    } else {
        int return_code = read_credentials_from_file(p_test_file, &got_data);
        if (return_code != 0) {
            return ERR_WRONG_READING_FROM_FILE;
        }
        fclose(p_test_file);
    }

    // пункт 3: проверка правильности чтения
    if (expected_data.number != got_data.number || expected_data.indebtedness != got_data.indebtedness ||
        expected_data.credit_limit != got_data.credit_limit || expected_data.cash_payments != got_data.cash_payments ||
        strcmp(expected_data.name, got_data.name) != 0 || strcmp(expected_data.surname, got_data.surname) != 0 ||
        strcmp(expected_data.address, got_data.address) != 0 ||
        strcmp(expected_data.tel_number, got_data.tel_number) != 0) {
        return ERR_WRONG_COMPARING;
    }
    return 0;
}

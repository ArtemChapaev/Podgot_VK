#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void invocation_enter_transaction();

int enter_transaction(data_t *transfer);

void write_to_file_transaction(FILE *const p_transaction_file, data_t transfer);

void write_transaction(FILE *const p_transaction_file) {
    invocation_enter_transaction();

    data_t transfer;
    int return_code = enter_transaction(&transfer);

    while (return_code == 0) {
        write_to_file_transaction(p_transaction_file, transfer);
        invocation_enter_transaction();
        return_code = enter_transaction(&transfer);
    }
}

void invocation_enter_transaction() {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");
}

int enter_transaction(data_t *transfer) {
    int return_code = scanf("%d", &transfer->number);
    if (return_code != 1) {
        return 1;
    }

    return_code = scanf("%lf", &transfer->cash_payments);
    if (return_code != 1) {
        return 1;
    } else {
        return 0;
    }
}

void write_to_file_transaction(FILE *const p_transaction_file, data_t transfer) {
    fprintf(p_transaction_file, "%-3d%-6.2f\n",
            transfer.number, transfer.cash_payments);
}

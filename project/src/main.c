#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "credentials_recording.h"
#include "transaction_recording.h"
#include "base_updating.h"
#include "helper.h"


int main(void) {
    invocation_choice();

    int choice = 0;
    while (scanf("%d", &choice) == 1) {
        switch (choice) {
            case ENT_DATA_CLIENT: {
                FILE *p_credentials_file;
                p_credentials_file = fopen(RECORD_FILE, "r+");

                if (p_credentials_file == NULL) {
                    printf(MESS_NO_FILE_OPENED, RECORD_FILE);
                    return ERR_NO_FILE_OPENED;
                }
                write_credentials(p_credentials_file);
                fclose(p_credentials_file);

                break;
            }

            case ENT_DATA_TRANS: {
                FILE *p_transaction_file = fopen(TRANSACTION_FILE, "r+");

                if (p_transaction_file == NULL) {
                    printf(MESS_NO_FILE_OPENED, TRANSACTION_FILE);
                    return ERR_NO_FILE_OPENED;
                }
                write_transaction(p_transaction_file);
                fclose(p_transaction_file);

                break;
            }

            case UPD_BASE: {
                FILE *p_credentials_file = fopen(RECORD_FILE, "r");
                FILE *p_transaction_file = fopen(TRANSACTION_FILE, "r");
                FILE *p_update_base_file = fopen(BASE_UPD_FILE, "w");

                if (p_credentials_file == NULL || p_transaction_file == NULL || p_update_base_file == NULL) {
                    printf(MESS_NO_3_FILES_OPENED, RECORD_FILE, TRANSACTION_FILE, BASE_UPD_FILE);
                    return ERR_NO_FILE_OPENED;
                }
                update_base(p_credentials_file, p_transaction_file, p_update_base_file);
                fclose(p_credentials_file);
                fclose(p_transaction_file);
                fclose(p_update_base_file);

                break;
            }

            default:
                printf("%s", MESS_WRONG_CHOICE);
                return ERR_WRONG_CHOICE;
        }
        invocation_choice();
    }
    return 0;
}

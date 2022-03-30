#ifndef PROJECT_INCLUDE_DATA_AND_RECORDING_H_
#define PROJECT_INCLUDE_DATA_AND_RECORDING_H_

#define RECORD_FILE "record.dat"
#define TRANSACTION_FILE "transaction.dat"
#define BASE_UPD_FILE "blackrecord.dat"

#define MESS_NO_FILE_OPENED "Not access to %s\n"
#define MESS_NO_3_FILES_OPENED "Not access to %s, %s, %s\n"
#define MESS_WRONG_CHOICE "Error, invalid choice\n"

enum data {
    PHONE = 15, PERSON = 20, ADDRESS = 30
};

enum mods {
    ENT_DATA_CLIENT = 1, ENT_DATA_TRANS = 2, UPD_BASE = 3
};

enum errors {
    ERR_WRONG_CHOICE = -2, ERR_NO_FILE_OPENED = -1, ERR_WRONG_INPUT = 1
};

struct master_record_t {
    int number;
    char name[PERSON];
    char surname[PERSON];
    char address[ADDRESS];
    char tel_number[PHONE];
    double indebtedness;
    double credit_limit;
    double cash_payments;
};
typedef struct master_record_t data_t;

#endif  // PROJECT_INCLUDE_DATA_AND_RECORDING_H_

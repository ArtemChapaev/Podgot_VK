#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

enum data {
    PHONE = 15, PERSON = 20, ADDRESS = 30, FORMAT_STRING_MAX_SIZE = 10
};

enum mods {
    ENT_DATA_CLIENT = 1, ENT_DATA_TRANS = 2, UPD_BASE = 3
};

enum errors {
    ERR_WRONG_CHOICE = -2, ERR_WRONG_FILE = -1
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

#endif  // PROJECT_INCLUDE_UTILS_H_

#ifndef PODGOT_VK_MAIL_PARSER_H
#define PODGOT_VK_MAIL_PARSER_H

#include <stdbool.h>

#define FROM "from"
#define TO "to"
#define DATE "date"
#define CONTENT_TYPE "content-type"

#define BUF_SIZE 128
#define OUTPUT_SIZE 512

typedef enum {
    STR,
    EMPTY_STR,
    H_FROM,
    H_TO,
    H_DATE,
    H_CONTENT_TYPE,
    H_OTHER,
    PART,
    END
} mod_t;

char *mail_parser(FILE *eml_file);

typedef int (*callback_t)(char *str, int mod);

int callback(char *str, int mod);

#endif //PODGOT_VK_MAIL_PARSER_H

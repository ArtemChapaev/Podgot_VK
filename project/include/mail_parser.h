#ifndef PROJECT_INCLUDE_MAIL_PARSER_H_
#define PROJECT_INCLUDE_MAIL_PARSER_H_

#include <stdbool.h>
#include <stdio.h>

#define FROM "from"
#define TO "to"
#define DATE "date"
#define CONTENT_TYPE "content-type"

#define BUF_SIZE 256
#define OUTPUT_SIZE 512
#define BOUNDARY_SIZE 64

#define END_OF_STR BUF_SIZE - 2

#define BOUNDARY_LEN 9

typedef enum {
    STR,
    H_FROM,
    H_TO,
    H_DATE,
    H_CONTENT_TYPE,
    H_OTHER,
    BEGIN_OF_BODY,
    END
} mod_t;

typedef enum {
    ERR_MEMORY = 1,
    ERR_WRONG_LEXEM,
} err_t;

#define NO_MULTYPART -1

typedef int (*callback_t)(char *str, mod_t mod);
int mail_parser(FILE *eml_file);
int callback(char *str, mod_t mod);

#endif  // PROJECT_INCLUDE_MAIL_PARSER_H_

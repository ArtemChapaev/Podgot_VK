#ifndef PROJECT_INCLUDE_MAIL_PARSER_H_
#define PROJECT_INCLUDE_MAIL_PARSER_H_

#include <stdbool.h>
#include <stdio.h>

#define FROM "from"
#define TO "to"
#define DATE "date"
#define CONTENT_TYPE "content-type"

#define BUF_SIZE 512
#define OUTPUT_SIZE 512
#define BOUNDARY_SIZE 64

#define BOUNDARY_LEN 9

typedef enum {
    STR,
    H_FROM,
    H_TO,
    H_DATE,
    H_CONTENT_TYPE,
    H_OTHER,
    BODY,
    NO_MULTYPART,
    END
} mod_t;

typedef enum {
    ERR_MEMORY = 1,
    ERR_WRONG_LEXEM,
} err_t;


typedef int (*callback_t)(char *str, mod_t mod, mod_t* output_mod);
int mail_parser(FILE *eml_file);
int callback(char *str, mod_t mod, mod_t* output_mod);

#endif  // PROJECT_INCLUDE_MAIL_PARSER_H_

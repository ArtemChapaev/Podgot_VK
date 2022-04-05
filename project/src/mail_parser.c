#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "mail_parser.h"

#define BUF_SIZE 128
#define OUTPUT_SIZE 512

typedef enum {
    L_HNAME,
    L_STR,
    L_SPACE_STR,
    L_EMPTY_STR,
    L_BOUNDARY,
    L_EOF,
    L_COUNT,
    L_ERR
} lexem_t;

static char *get_lexem(FILE *file, lexem_t *lexem);

void str_translate(lexem_t *lexem, int j, char *buf);

char *mail_parser(FILE *eml_file) {
    //state_t state = S_BEGIN;
    lexem_t lexem;
    char *str = get_lexem(eml_file, &lexem);
    while (lexem != L_EOF) {
        if (lexem == L_ERR) {
            printf("ERR\n");
            free(str);
            return NULL;
        }
        free(str);
        str = get_lexem(eml_file, &lexem);
    }
    return NULL;
}

static char *get_lexem(FILE *file, lexem_t *lexem) {
    static bool is_header_value = false;

    char *buf = malloc(BUF_SIZE);
    int j = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
            case ('\n'): {
                char next = fgetc(file);
                if (next != '\r') {
                    ungetc(next, file);
                }

                str_translate(lexem, j, buf);
                is_header_value = false;
                return buf;
            }
            case ('\r'): {
                char next = fgetc(file);
                if (next != '\n') {
                    ungetc(next, file);
                }

                str_translate(lexem, j, buf);
                is_header_value = false;
                return buf;
            }
            case (':'): {
                if (j == 0) {
                    *lexem = L_ERR;
                } else if (is_header_value) {
                    buf[j++] = ch;
                    break;
                } else {
                    is_header_value = true;
                    buf[j] = '\0';
                    *lexem = L_HNAME;
                }
                return buf;
            }
            case (' '): {
                if (is_header_value && j == 0) {
                    break;
                } else if (j == 0) {
                    *lexem = L_SPACE_STR;
                    for (; ((ch = fgetc(file)) != '\n' && ch != '\r') && (j < BUF_SIZE - 1); ++j) {
                        buf[j] = ch;
                    }
                    if (ch == '\n') {
                        char next = fgetc(file);
                        if (next != '\r') {
                            ungetc(next, file);
                        }
                    }
                    if (ch == '\r') {
                        char next = fgetc(file);
                        if (next != '\n') {
                            ungetc(next, file);
                        }
                    }
                    buf[j] = '\0';
                    return buf;
                } else {
                    buf[j++] = ch;
                    break;
                }
            }
            default: {
                buf[j++] = ch;
            }
        }
    }
    *lexem = L_EOF;
    free(buf);
    return NULL;
}

void str_translate(lexem_t *lexem, int j, char *buf) {
    if (j == 0) {
        *lexem = L_EMPTY_STR;
    } else {
        *lexem = L_STR;
    }
    buf[j] = '\0';
    return;
}

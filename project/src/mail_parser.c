#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"
#include "actions.h"

typedef int (*action_t)(char *str, callback_t callback);

typedef enum {
    L_HNAME,
    L_STR,
    L_EMPTY_STR,
    L_EOF,
    L_COUNT,
    L_ERR
} lexem_t;

typedef enum {
    S_BEGIN,
    S_HNAME,
    S_HVALUE,
    S_HEND,
    S_PART,
    S_END,
    S_COUNT,
    S_ERR
} state_t;

typedef struct {
    state_t state;
    action_t action;
} rule_t;

char *get_lexem(FILE *file, lexem_t *lexem);
int buf_realloc(char **buf, int *overflow_count);
void check_next_sym(FILE *file, char ch);
void check_line_feed(lexem_t *lexem, int j, char *buf, bool *is_header_value, bool *is_part_file);

static rule_t transitions[S_COUNT][L_COUNT] = {
//                  L_HNAME                 L_STR                   L_EMPTY_STR             L_EOF
/*S_BEGIN*/         {{S_HNAME, valid_h}, {S_ERR, NULL},             {S_ERR,  NULL},         {S_ERR, NULL}},
/*S_HNAME*/         {{S_ERR,  NULL},     {S_HVALUE, str_check},     {S_ERR,  NULL},         {S_ERR, NULL}},
/*S_HVALUE*/        {{S_HNAME, valid_h}, {S_HVALUE, str_check},     {S_HEND, part_begin},   {S_ERR, NULL}},
/*S_HEND*/          {{S_PART, NULL},     {S_PART,   str_check},     {S_HEND, part_begin},   {S_END, finish}},

/*S_PART*/          {{S_PART, NULL},     {S_PART,   str_check},     {S_PART, NULL},         {S_END, finish}},
/*S_END*/           {{S_ERR,  NULL},     {S_ERR, NULL},             {S_ERR,  NULL},         {S_ERR, NULL}}
};

int mail_parser(FILE *eml_file) {
    state_t state = S_BEGIN;
    lexem_t lexem;

    while (true) {
        char *str = get_lexem(eml_file, &lexem);
        if (str == NULL) {
            return ERR_MEMORY;
        }

        rule_t rule = transitions[state][lexem];
        if (rule.state == S_ERR) {
            free(str);
            return ERR_WRONG_LEXEM;
        }

        if (rule.action != NULL) {
            int return_code = rule.action(str, callback);
            if (return_code != 0) {
                free(str);
                return ERR_MEMORY;
            }
        }

        state = rule.state;
        free(str);
        if (lexem == L_EOF) {
            break;
        }
    }
    return 0;
}

char *get_lexem(FILE *file, lexem_t *lexem) {
    static bool is_header_value = false;
    static bool is_part_file = false;

    char *buf = calloc(BUF_SIZE, sizeof(char));
    if (buf == NULL) {
        return NULL;
    }
    int j = 0;

    int overflow_count = 1;

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
            case '\n': {
                check_next_sym(file, '\r');
                check_line_feed(lexem, j, buf, &is_header_value, &is_part_file);
                return buf;
            }
            case '\r': {
                check_next_sym(file, '\n');
                check_line_feed(lexem, j, buf, &is_header_value, &is_part_file);
                return buf;
            }
            case ':': {
                if (is_header_value || is_part_file) {  // возможно наличие ':' в строке
                    buf[j++] = ch;                      // с заголовком или в теле
                    break;
                } else {
                    is_header_value = true;
                    buf[j] = '\0';
                    *lexem = L_HNAME;
                    return buf;
                }
            }
            case '\t':
            case ' ': {
                if (is_header_value && j == 0) {  // обрабатывается пробел после имени заголовка
                } else if (j == 0) {
                    *lexem = L_STR;

                    while (isspace(ch)) {
                        ch = fgetc(file);
                    }
                    buf[j++] = ch;

                    // fgets, но без считывания перевода строки
                    for (; (((ch = fgetc(file)) != EOF) && ch != '\n' && ch != '\r'); ++j) {
                        buf[j] = ch;
                        if (j >= END_OF_STR) {
                            if (buf_realloc(&buf, &overflow_count) != 0) {
                                return NULL;
                            }
                        }
                    }

                    // чтобы ничего не осталось для следующего лексического разбора
                    if (ch == '\n') {
                        check_next_sym(file, '\r');
                    } else if (ch == '\r') {
                        check_next_sym(file, '\n');
                    }

                    buf[j] = '\0';
                    return buf;
                } else {
                    if (j >= END_OF_STR) {
                        if (buf_realloc(&buf, &overflow_count) != 0) {
                            return NULL;
                        }
                    }
                    buf[j++] = ch;
                }
                break;
            }
            default: {
                if (j >= END_OF_STR) {
                    if (buf_realloc(&buf, &overflow_count) != 0) {
                        return NULL;
                    }
                }
                buf[j++] = ch;
            }
        }
    }
    if (j != 0) {
        *lexem = L_STR;
    } else {
        *lexem = L_EOF;
    }
    buf[j] = '\0';
    return buf;
}

int buf_realloc(char **buf, int *overflow_count) {
    ++(*overflow_count);
    char *new_buf = realloc(*buf, (*overflow_count) * BUF_SIZE);
    if (new_buf == NULL) {
        return ERR_MEMORY;
    }
    *buf = new_buf;
    return 0;
}

void check_next_sym(FILE *file, char ch) {
    char next = fgetc(file);
    if (next != ch) {
        ungetc(next, file);
    }
}

void check_line_feed(lexem_t *lexem, int j, char *buf, bool *is_header_value, bool *is_part_file) {
    if (j == 0 && !(*is_header_value)) {
        *lexem = L_EMPTY_STR;
        *is_part_file = true;
    } else {
        *lexem = L_STR;
    }

    buf[j] = '\0';
    *is_header_value = false;
    return;
}

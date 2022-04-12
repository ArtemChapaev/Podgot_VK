#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"
#include "actions.h"

typedef int (*action_t)(char *str, callback_t callback, mod_t *mod);

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

void free_arrays(char *buf_1, char *buf_2, char *buf_3, char *buf_4);

char *get_lexem(FILE *file, lexem_t *lexem);

int buf_realloc(char **buf, int *overflow_count);

void check_next_sym(FILE *file, char ch);

void check_line_feed(lexem_t *lexem, int j, char *buf, bool *is_header_value, bool *is_part_file);

int add_str(char **dest_str, char *str);

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
    char *from_str = malloc(OUTPUT_SIZE);
    if (from_str == NULL) {
        return ERR_MEMORY;
    }
    char *to_str = malloc(OUTPUT_SIZE);
    if (to_str == NULL) {
        free(from_str);
        return ERR_MEMORY;
    }
    char *date_str = malloc(OUTPUT_SIZE);
    if (date_str == NULL) {
        free_arrays(from_str, to_str, NULL, NULL);
        return ERR_MEMORY;
    }

    int p_count = 0;

    from_str[0] = '\0';
    to_str[0] = '\0';
    date_str[0] = '\0';

    state_t state = S_BEGIN;
    lexem_t lexem;

    char *str = get_lexem(eml_file, &lexem);
    if (str == NULL) {
        free_arrays(from_str, to_str, date_str, NULL);
        return ERR_MEMORY;
    }

    while (lexem != L_EOF) {
        rule_t rule = transitions[state][lexem];
        if (rule.state == S_ERR) {
            free_arrays(from_str, to_str, date_str, str);
            return ERR_WRONG_LEXEM;
        }

        if (rule.action != NULL) {
            mod_t mod = 0;
            int return_code = rule.action(str, callback, &mod);
            if (return_code != 0) {
                free_arrays(from_str, to_str, date_str, str);
                return ERR_MEMORY;
            }

            switch (mod) {
                case H_FROM: {
                    return_code = add_str(&from_str, str);
                    if (return_code != 0) {
                        free_arrays(from_str, to_str, date_str, str);
                        return ERR_MEMORY;
                    }
                    break;
                }
                case H_TO: {
                    return_code = add_str(&to_str, str);
                    if (return_code != 0) {
                        free_arrays(from_str, to_str, date_str, str);
                        return ERR_MEMORY;
                    }
                    break;
                }
                case H_DATE: {
                    return_code = add_str(&date_str, str);
                    if (return_code != 0) {
                        free_arrays(from_str, to_str, date_str, str);
                        return ERR_MEMORY;
                    }
                    break;
                }
                case NO_MULTYPART: {
                    p_count = 1;
                    break;
                }
                case BODY: {
                    p_count++;
                    break;
                }
                default: {
                    break;
                }
            }
        }

        state = rule.state;
        free(str);

        str = get_lexem(eml_file, &lexem);
        if (str == NULL) {
            free_arrays(from_str, to_str, date_str, NULL);
            return ERR_MEMORY;
        }
    }
    printf("%s|%s|%s|%d\n", from_str, to_str, date_str, p_count);
    free_arrays(from_str, to_str, date_str, str);
    return 0;
}

void free_arrays(char *buf_1, char *buf_2, char *buf_3, char *buf_4) {
    free(buf_1);
    free(buf_2);
    if (buf_3 != NULL) {
        free(buf_3);
        if (buf_4 != NULL) {
            free(buf_4);
        }
    }
}

char *get_lexem(FILE *file, lexem_t *lexem) {
    static bool is_header_value = false;
    static bool is_part_file = false;

    char *buf = calloc(BUF_SIZE, sizeof(char));
    if (buf == NULL) {
        return NULL;
    }
    int j = 0;

    int overflow_count = 1;   // переменная для подсчета кол-ва обращений к realloc-у

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
                        if (j >= overflow_count * BUF_SIZE - 2) {
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
                    if (j >= overflow_count * BUF_SIZE - 2) {
                        if (buf_realloc(&buf, &overflow_count) != 0) {
                            return NULL;
                        }
                    }
                    buf[j++] = ch;
                }
                break;
            }
            default: {
                if (j >= overflow_count * BUF_SIZE - 2) {
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

int add_str(char **dest_str, char *str) {
    int len = 0;
    for (; (*dest_str)[len] != '\0'; ++len) {}  // если строка была не пустой, считаю ее
    if (len != 0) {                             // занятые элементы
        (*dest_str)[len] = ' ';
        (*dest_str)[len + 1] = '\0';
    }

    int overflow_count = 1;                     // переменная для подсчета кол-ва обращений к realloc-у
    int len_str = strlen(str);

    while (len_str > overflow_count * OUTPUT_SIZE - len - 1) {
        if (buf_realloc(dest_str, &overflow_count) != 0) {  // корректный вызов и проверка realloc-a
            return ERR_MEMORY;
        }
    }
    strncat(*dest_str, str, overflow_count * OUTPUT_SIZE - len - 2);
    return 0;
}

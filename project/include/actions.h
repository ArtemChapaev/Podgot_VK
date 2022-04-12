#ifndef PROJECT_INCLUDE_ACTIONS_H_
#define PROJECT_INCLUDE_ACTIONS_H_

#include "mail_parser.h"

int valid_h(char *header, callback_t callback, mod_t* mod);
int str_check(char *str, callback_t callback, mod_t* mod);
int part_begin(char *str, callback_t callback, mod_t* mod);
int finish(char *str, callback_t callback, mod_t* mod);

#endif  // PROJECT_INCLUDE_ACTIONS_H_

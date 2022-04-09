#ifndef PODGOT_VK_MAIL_ACTIONS_H
#define PODGOT_VK_MAIL_ACTIONS_H


int valid_h(char *header, callback_t callback);

int str_check(char *header, callback_t callback);

int part_begin(char *header, callback_t callback);

int finish(char *header, callback_t callback);

#endif //PODGOT_VK_MAIL_ACTIONS_H

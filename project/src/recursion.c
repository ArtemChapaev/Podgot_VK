#include "recursion.h"

void numbers_to_one(int num, int output_num) {
    if (output_num == num) {
        printf("%d\n", output_num);     // условие завершения рекурсии
        return;
    } else if (num > 1) {
        printf("%d ", output_num);      // продолжение рекурсии при num > 1
        numbers_to_one(num, output_num + 1);
    } else {
        printf("%d ", output_num);      // продолжение рекурсии при num < 1
        numbers_to_one(num, output_num - 1);
    }
}

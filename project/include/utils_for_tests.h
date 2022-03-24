#ifndef PROJECT_INCLUDE_UTILS_FOR_TESTS_H_
#define PROJECT_INCLUDE_UTILS_FOR_TESTS_H_

#define UNIT_TEST_FILE "unit_test.dat"
#define FULL_TEST_FILE "full_test.dat"

#define ERROR_MESSAGE "ERROR!\n"
#define CORRECT_END_MESSAGE "Correct ending\n"

enum test_errors {
    ERR_WRONG_READING = 2, ERR_WRONG_COMPARING = 3, ERR_WRONG_READING_FROM_FILE = 4,
    ERR_WRONG_TEST = 6
};

#endif  // PROJECT_INCLUDE_UTILS_FOR_TESTS_H_

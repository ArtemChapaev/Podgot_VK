TARGET = ./main.out
HDRS_DIR = project/include

SRCS = project/src/main.c \
		project/src/credentials_recording.c \
		project/src/transaction_recording.c \
		project/src/base_updating.c \
		project/src/helper.c

.PHONY: all build rebuild check test memtest clean \
		build_ftest rebuild_ftest check_ftest test_ftest memtest_ftest clean_ftest \
		build_rtest rebuild_rtest check_rtest test_rtest memtest_rtest clean_rtest \
		build_wtest rebuild_wtest check_wtest test_wtest memtest_wtest clean_wtest

all: clean check test memtest clean_ftest check_ftest test_ftest memtest_ftest \
		clean_rtest check_rtest test_rtest memtest_rtest clean_wtest check_wtest test_wtest memtest_wtest

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat

# For full_test.c

TARGET_FULL_TEST = ./full_test.out

SRCS_FULL_TEST = tests/full_test.c \
		project/src/credentials_recording.c \
		project/src/base_updating.c

$(TARGET_FULL_TEST): $(SRCS_FULL_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_FULL_TEST) $(CFLAGS) $(SRCS_FULL_TEST)

build_ftest: $(TARGET_FULL_TEST)

rebuild_ftest: clean_ftest build_ftest

check_ftest:
	./run_linters.sh

test_ftest: $(TARGET_FULL_TEST)
	./btests/run_full_test.sh $(TARGET_FULL_TEST)

memtest_ftest: $(TARGET_FULL_TEST)
	./btests/run_full_test.sh $(TARGET_FULL_TEST) --memcheck

clean_ftest:
	rm -rf $(TARGET_FULL_TEST) *.dat


# For read_test.c

TARGET_READ_TEST = ./read_test.out

SRCS_READ_TEST = tests/read_test.c \
		project/src/base_updating.c

$(TARGET_READ_TEST): $(SRCS_READ_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_READ_TEST) $(CFLAGS) $(SRCS_READ_TEST)

build_rtest: $(TARGET_READ_TEST)

rebuild_rtest: clean_rtest build_rtest

check_rtest:
	./run_linters.sh

test_rtest: $(TARGET_READ_TEST)
	./btests/run_unit_test.sh $(TARGET_READ_TEST) --read

memtest_rtest: $(TARGET_READ_TEST)
	./btests/run_unit_test.sh $(TARGET_READ_TEST) --read --memcheck

clean_rtest:
	rm -rf $(TARGET_READ_TEST) *.dat


# For write_test.c

TARGET_WRITE_TEST = ./write_test.out

SRCS_WRITE_TEST = tests/write_test.c \
		project/src/credentials_recording.c

$(TARGET_WRITE_TEST): $(SRCS_WRITE_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_WRITE_TEST) $(CFLAGS) $(SRCS_WRITE_TEST)

build_wtest: $(TARGET_WRITE_TEST)

rebuild_wtest: clean_wtest build_wtest

check_wtest:
	./run_linters.sh

test_wtest: $(TARGET_WRITE_TEST)
	./btests/run_unit_test.sh $(TARGET_WRITE_TEST) --write

memtest_wtest: $(TARGET_WRITE_TEST)
	./btests/run_unit_test.sh $(TARGET_WRITE_TEST) --write --memcheck

clean_wtest:
	rm -rf $(TARGET_WRITE_TEST) *.dat

TARGET = ./main.out
TST_TARGET = ./tests.out

# Main
HDRS_DIR = project/include

SRCS = project/src/main.c \
		project/src/credentials_recording.c \
		project/src/transaction_recording.c \
		project/src/base_updating.c \
		project/src/invocation_choice.c

# Tests
TST_HDRS_DIR = project/include \
				tests/include

TST_SRCS = tests/src/main.c \
		tests/src/full_test.c \
		tests/src/read_test.c \
		tests/src/write_test.c \
		project/src/credentials_recording.c \
		project/src/base_updating.c


.PHONY: all build rebuild check test memtest clean \
		build_test rebuild_test test_test clean_test

all: clean check test memtest clean_test test_test


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


$(TST_TARGET): $(TST_SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror $(addprefix -I,$(TST_HDRS_DIR)) -o $(TST_TARGET) $(CFLAGS) $(TST_SRCS)

build_test: $(TST_TARGET)

rebuild_test: clean_test build_test

test_test: $(TST_TARGET)
	./btests/run_tests.sh $(TST_TARGET)

clean_test:
	rm -rf $(TST_TARGET) *.dat

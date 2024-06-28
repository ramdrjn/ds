INC_DIR=./include
CC=gcc
CFLAGS=-I$(INC_DIR)
CFLAGS+=-Wall #-Wextra
LFLAGS+=-g -O0 -Wall -Wextra
GCOV_OPTS= #-fprofile-arcs -ftest-coverage

src_files=$(src) $(INC_DIR)/utest/utest_main.c
src_objs=$(src_files:%.c=%.o)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(GCOV_OPTS)

out.bin: $(src_objs)
	$(CC) -o $@ $^ $(LFLAGS) $(GCOV_OPTS)

coverage: ## Run code coverage
	gcov $(src_files)

.Phony: clean
clean:
	$(RM) out.bin
	$(RM) $(src_objs)
	find . -iname "*.gcda" -exec rm {} \;
	find . -iname "*.gcno" -exec rm {} \;
	find . -iname "*.gcov" -exec rm {} \;

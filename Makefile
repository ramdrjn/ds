INC_DIR=./include
GCOV_OPTS=-fprofile-arcs -ftest-coverage

out.bin: $(src) $(INC_DIR)/utest/utest_main.c
	gcc -g -O0 -Wall $(GCOV_OPTS) -I$(INC_DIR) $^ -o $@

.Phony: clean
clean:
	rm out.bin

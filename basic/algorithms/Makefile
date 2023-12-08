INC_DIR=../../include

out.bin: $(src) $(INC_DIR)/utest/utest_main.c
	gcc -g -O0 -Wall -I$(INC_DIR) $^ -o $@

.Phony: clean
clean:
	rm out.bin

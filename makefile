ASM_SOURCES := instruction_nop_100.s
C_SOURCES := main.cpp
NAME := get_a_better_keyboard
CC := g++

# Verify your binary by running
# objdumb -d executable name > output.s

.PHONY: build
$(NAME):
	$(CC) $(C_SOURCES) $(ASM_SOURCES) -o $(NAME)

.PHONY: clean
clean:
	rm -rf $(NAME)
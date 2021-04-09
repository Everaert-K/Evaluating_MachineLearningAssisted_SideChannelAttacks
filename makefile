# ASM_SOURCES := src/instruction_nop_100.s
ASM_SOURCES := src/assembly/*_movl_*.s
C_SOURCES := src/main.cpp
NAME := energy
CC := g++

# Verify your binary by running
# objdumb -d executable name > output.s

.PHONY: build
$(NAME):
	$(CC) -g $(C_SOURCES) $(ASM_SOURCES) -o $(NAME) -lpthread -pthread

.PHONY: clean
clean:
	rm -rf $(NAME)
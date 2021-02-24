# ASM_SOURCES := src/instruction_nop_100.s
ASM_SOURCES := src/assembly/*.s
C_SOURCES := src/main.cpp
NAME := energy
CC := g++

# Verify your binary by running
# objdumb -d executable name > output.s

.PHONY: build
$(NAME):
	$(CC) $(C_SOURCES) $(ASM_SOURCES) -o $(NAME)

.PHONY: clean
clean:
	rm -rf $(NAME)
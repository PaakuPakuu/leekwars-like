NAME=leekwars
C_FILES = $(wildcard src/*.c)
O_FILES = $(C_FILES:src/%.c=build/%.o)
#Compilateur
CC = gcc

#Options du compilateur
CFLAGS = -Wall -pedantic -ansi -g
LDFLAGS = -lm

.PHONY: all clean
.DEFAULT: all
all: $(NAME)

$(NAME): $(C_FILES) | build
	@$(CC) $(CFLAGS) -o $@ $^
	@mv $(NAME) build

build:
	@mkdir -p build
	@cp -r src/Strats build

clean:
	@rm -f $(NAME)*
	@rm -fr build

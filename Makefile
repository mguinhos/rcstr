NAME= test-rcstr

ifeq ($(OS), Windows_NT)
	NAME_EXT= $(NAME).exe
else
	NAME_EXT= $(NAME)
endif

CC= clang
CC_INCLUDES= -Iinclude

all:
	$(CC) main.c -o $(NAME_EXT) $(CC_INCLUDES)

run:
	./$(NAME_EXT)


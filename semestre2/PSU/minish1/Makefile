##
## EPITECH PROJECT, 2024
## MiniShell1
## File description:
## Makefile
##

SRC		=	src/main.c					\
			src/builtins.c				\
			src/commands.c				\
			src/str_to_word_array.c		\
			src/my_cd.c					\
			src/get_clean_exec.c		\
			src/setenv.c				\
			src/unsetenv.c				\
			src/my_fork.c

NAME	=	mysh

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy -Wall -Wextra

all:		libmy.a		$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) > /dev/null
			@echo "Compilation done"

clean:
			@make -C lib/my clean > /dev/null
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@make -C lib/my fclean > /dev/null
			@rm -f $(NAME)
			@rm -f libmy.a
			@echo "Full cleaning done."

re:			fclean all

libmy.a:
			@echo "Compiling lib"
			@make -C lib/my > /dev/null
			@cp lib/my/libmy.a .

debug:		libmy.a		$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) -g

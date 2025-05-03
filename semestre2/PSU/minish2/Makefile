##
## EPITECH PROJECT, 2024
## MiniShell2
## File description:
## Makefile
##

SRC		=	src/main.c											\
			src/env/getenv.c									\
			src/env/freeenv.c									\
			src/env/setenv.c									\
			src/env/unsetenv.c									\
			src/builtins/env.c									\
			src/builtins/cd.c									\
			src/builtins/exit.c									\
			src/builtins/run_builtins.c							\
			src/utilities/free.c								\
			src/utilities/utilities.c							\
			src/utilities/parsing.c								\
			src/command/run_command.c							\
			src/command/fork.c									\
			src/pipeline/exec_pipes.c							\
			src/pipeline/parse_pipes.c							\
			src/pipeline/fork_pipe.c							\
			src/redirections/check_redirections.c				\
			src/redirections/exec_redirections.c				\
			src/redirections/fork_redirections.c				\
			src/redirections/path_redirection_command.c			\

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
			@gcc -o $(NAME) $(OBJ) $(CFLAGS)

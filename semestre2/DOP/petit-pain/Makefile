##
## EPITECH PROJECT, 2024
## makefile
## File description:
## chocolatine
##

SRC		=	code.c

SRC_TEST	=	code.c \
				tests/test_choco.c

NAME	=	petit_pain

OBJ		=	$(SRC:.c=.o)

all:		$(OBJ)
			gcc -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

tests_run:
			@echo "Tests running"

##
## EPITECH PROJECT, 2024
## makefile
## File description:
## 101pong
##

SRC		=	main.c			\
			bat_functions.c	\
			other.c

NAME	=	my_hunter

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy

all:		libmy.a $(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS) \
			-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			make -C lib/my fclean

libmy.a:
		make -C lib/my


re:			fclean all

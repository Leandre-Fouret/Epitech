##
## EPITECH PROJECT, 2024
## makefile
## File description:
## myradar
##

SRC		=	main.c					\
			file_verification.c		\
			interpret_file.c		\
			display.c				\
			movement.c				\
			handle_collisions.c		\
			free.c

NAME	=	my_radar

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy -lm -Wall -Wextra

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

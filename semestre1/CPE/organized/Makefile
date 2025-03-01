##
## EPITECH PROJECT, 2024
## makefile
## File description:
## organized
##

SRC		=	main.c			\
			add_display.c	\
			delete.c		\
			sort.c			\
			sort_name.c		\
			sort_type.c		\
			sort_id.c

NAME	=	organized

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lshell -lmy -Wall -Wextra

all:		libmy.a		$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
			make -C lib/my clean
			rm -f $(OBJ)

fclean:		clean
			make -C lib/my fclean
			rm -f $(NAME)
			rm -f libmy.a

re:			fclean all

libmy.a:
			make -C lib/my
			cp lib/my/libmy.a .

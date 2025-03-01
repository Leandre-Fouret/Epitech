##
## EPITECH PROJECT, 2024
## makefile
## File description:
## 101pong
##

SRC		=	main.c				\
			square_finding.c	\
			map.c				\
			settingup_func.c

NAME	=	setting_up

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I include -L lib/my -lmy

all:		libmy.a $(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
			make -C lib/my clean
			rm -f $(OBJ)

fclean:
			make -C lib/my fclean
			rm -f $(NAME)
			rm -f libmy.a

re:			fclean all

libmy.a:
			make -C lib/my
			cp lib/my/libmy.a .

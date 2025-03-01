##
## EPITECH PROJECT, 2024
## root Makefile
## File description:
## make
##

SRC 	=	main.c

SRC_TEST	=	lib/my/my_printf/my_printf.c			\
				lib/my/my_printf/printf_putchar.c		\
				lib/my/my_printf/printf_putnbr.c		\
				lib/my/my_printf/printf_putstr.c		\
				lib/my/my_printf/utilities.c			\
				lib/my/my_printf/printf_putfloat.c		\
				lib/my/my_printf/parse_flags.c			\
				lib/my/my_printf/printf_putbase.c		\
				lib/my/my_printf/utilities2.c			\
				lib/my/my_printf/printf_scientific.c	\
				lib/my/my_printf/utilities3.c			\
				lib/my/my_printf/printf_n_spec.c		\
				lib/my/my_printf/printf_g_spec.c		\
				lib/my/my_printf/manage_spec.c		    \
				lib/my/my_printf/put_buffer.c			\
				tests/test_my_printf.c


NAME	=	test

OBJ 	=	$(SRC:.c=.o)

all:	libmy.a

tests: 	libmy.a 	$(NAME)

CFLAGS	= -Iinclude -Llib/my -lmy

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		make clean -C lib/my
		rm -f $(OBJ)

fclean: clean
		make fclean -C lib/my
		rm -f $(NAME)
		rm -f libmy.a

re:		fclean all

libmy.a:
		make -C lib/my
		cp lib/my/libmy.a .

unit_tests:	fclean libmy.a
		gcc $(SRC_TEST) lib/my/libmy.a -I include \
		--coverage -lcriterion -o unit_tests

tests_run: unit_tests
		./unit_tests

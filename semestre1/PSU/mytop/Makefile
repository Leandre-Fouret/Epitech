##
## EPITECH PROJECT, 2024
## makefile
## File description:
## 101pong
##

SRC		=	main.c				\
			top_bar.c			\
			cpu_mem.c			\
			swap.c				\
			process_list.c		\
			add_processes.c		\
			display_processes.c	\
			time.c				\
			cpu_mem_column.c

NAME	=	my_top

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-lncurses -Wextra -Wall

all:		$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

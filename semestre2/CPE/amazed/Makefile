##
## EPITECH PROJECT, 2024
## Amazed
## File description:
## Makefile
##

SRC		=	src/main/main.c									\
			src/main/exec_main.c							\
			src/free/free_stdin.c							\
			src/free/free_rooms.c							\
			src/free/free_arrays.c							\
			src/handle_input/store_input.c					\
			src/handle_input/sort_input.c					\
			src/utilities/append_node.c						\
			src/utilities/utilities.c						\
      		src/pre_check/check_nb_bots.c         			\
			src/output/browse_line.c						\
			src/output/check_coordinates.c 					\
			src/output/check_names.c 						\
			src/output/check_params.c						\
			src/output/browse_tunnels.c						\
			src/algorithme/main_algo.c						\
			src/algorithme/matrix.c							\
			src/algorithme/algo_dijkstra.c 					\
			src/algorithme/move_bots.c


NAME	=	amazed

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy -Wall -Wextra -g

all: $(NAME)

$(NAME): 	libmy.a $(OBJ)
			@echo "[-] Compiling $(NAME) [-]"
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) > /dev/null
			@echo "[V] Successfully compiled $(NAME) [V]"

clean:
			@make -C lib/my clean > /dev/null
			@rm -f $(OBJ)
			@echo "[!] Removed object files. [!]"

fclean: clean
			@make -C lib/my fclean > /dev/null
			@rm -f $(NAME)
			@rm -f libmy.a
			@echo "[!] Removed $(NAME) binary. [!]"

re: fclean all

libmy.a:
			@echo "[-] Compiling lib [-]"
			@make -C lib/my > /dev/null
			@cp lib/my/libmy.a .
			@echo "[V] Lib successfully compiled ! [V]"

debug: $(NAME)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) -g
			@echo "[V] Successfully compiled $(NAME) with g flag [V]"

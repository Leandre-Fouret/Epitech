##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Runs the program
##

SRC		= 	src/main.c \
			src/utilities.c \
			src/int_to_str.c \
			src/has_permissions.c \
			src/change_id.c \
			src/flags/flags_detection.c \
			src/flags/flag_e.c \
			src/flags/flag_s.c	\
			src/flags/flag_u.c

OBJ = $(SRC:.c=.o)

CRIT = -lcriterion --coverage

FLAGS = -W -Wall -Wextra -I. -lcrypt

DFLAGS = $(FLAGS) -g

NAME	=	my_sudo

GREEN   = \e[1;32m
BLUE    = \e[1;34m
YELLOW  = \e[1;33m
RED     = \e[1;31m
RESET   = \e[0m

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(FLAGS)
	@echo -e "$(GREEN)[+++] Compilation done.\n./$(NAME) my G.$(RESET)"

%.o: %.c
	@echo -e "$(BLUE)[Compiling $< to $@]$(RESET)"
	@cc -c $< -o $@ $(FLAGS)

clean:
	@echo -e "$(RED)[-] Removing object files...$(RESET)"
	@rm -f $(NAME)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@find . -type f -name "*.o" -delete
	@echo -e "$(RED)[-] Cleaning done.$(RESET)"

fclean:	clean
	@echo -e "$(YELLOW)[-] Removing $(NAME) binary...$(RESET)"
	@rm -f $(OBJ)
	@rm -f *~
	@rm -f /*~
	@rm -f *#
	@rm -f *.g*
	@rm -f *.o
	@echo -e "$(YELLOW)[-] Fcleaning done.$(RESET)"

re:     fclean all

debug: $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(DFLAGS)
	@echo "$(GREEN)[+++] Compilation done with debugging. \n\
	valgrind ./$(NAME). Have no fun.$(RESET)"

tests_run: $(NAME)
	gcc -o $(TEST_NAME) $(SRC) $(SRC_TEST) $(CRIT)
	./$(TEST_NAME)

coverage: gcovr --exclude tests/

among_us:
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀$(RESET)"
	@echo -e "$(RED)⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀$(RESET)"
	@echo -e "$(RED)⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀$(RESET)"
	@echo -e "$(RED)⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀$(RESET)"
	@echo -e "$(RED)⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)"

.PHONY: all clean fclean re debug tests_run coverage

set_root:	all
	@sudo chown root:root $(NAME)
	@sudo chmod u+s $(NAME)

valgrinding: all
	@sudo chown root:root $(NAME)
	@sudo chmod -s $(NAME)
	@valgrind ./my_sudo
	@sudo chmod u+s $(NAME)

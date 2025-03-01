/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** Include file
*/

#ifndef MINISHELL1_H
    #define MINISHELL1_H
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "my.h"
    #include <string.h>
    #include <sys/types.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <stdint.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/sysmacros.h>
    #define STRING_SIZE 2048

typedef struct env_linked_s {
    char *key;
    char *value;
    struct env_linked_s *next;
} env_linked_t;

struct word_array {
    char **tab;
    char delimiter;
};

// MAIN EXECUTION
void clean_input(char *input);
int run_shell(env_linked_t **head, int *return_status, int *exit,
    char *current_previous);
int add_node(env_linked_t **head, env_linked_t *node);
void run_command(char *user_input, env_linked_t **head, int *return_status);

// BUILTINS
int run_builtins(char *user_input, env_linked_t **head, int *status,
    char *current_previous);
int my_cd(char *user_input, env_linked_t **head, char *current_previous);
int unset_myenv(env_linked_t **head, char *user_input);
int set_myenv(env_linked_t **head, char *user_input);
void display_env(env_linked_t **head);
int my_exit(char *user_input, int *exit_status);

//UTILITIES
char **str_in_array(char *str, char delimiter);

//FORK
void my_fork(char *path, char ***tab_fork, int *status);
void free_command_related(char *path, char ***tab_fork);
int fork_exceptions(char ***tab_fork, int *status, char *path);
void handle_fork_errors(char ***tab_fork, int *status, char *path,
    int *return_status);

#endif

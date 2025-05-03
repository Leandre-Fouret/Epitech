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
    #define MAX_INPUT_SIZE 4096
    #define NB_BUILT_IN 5
    #define MAX_COMMANDS 256
    #define NB_REDIRECTIONS 4


typedef struct env_s {
    char *key;
    char *value;
    struct env_s *next;
} env_t;

typedef struct {
    char *home;
    char *tmp_home;
    char *current_dir;
    char *new_dir;
} cd_t;

typedef struct {
    env_t **head;
    char **envp;
    int ac;
    char **av;
    int exit_code;
    int to_exit;
    char ***user_input;
    int command_index;
    cd_t cd;
    char *current_previous;
    int status;
    int redirect_type;
    char *command_path;
} params_t;

typedef struct pipes_s {
    int index;
    int subindex;
    int type;
    char **command;
    char *command_path;
    int read_end;
    int write_end;
    struct pipes_s *next;
} pipes_t;

typedef struct {
    char *command;
    void (*builtin_func)(params_t *);
} tab_builtins_t;

typedef struct {
    char *redirection;
    int out;
    int exit;
} tab_redirections_space_t;

typedef struct {
    char delimiter;
    int exit;
} tab_redirections_glue_t;

// ENVIRONMENT
env_t **get_all_env(char **envp);
void free_env(env_t **head);
void set_myenv(params_t *myshell);
void unset_myenv(params_t *myshell);
int add_node(env_t **head, env_t *node);


// BUILTINS
int run_builtins(params_t *myshell);
void display_env(params_t *myshell);
void my_exit(params_t *myshell);
void my_cd(params_t *myshell);


// UTILITIES
void free_double_arr(char **arr);
int is_printable(char *str, size_t len_read);
void free_triple_array(char ***arr);
char **dup_double_arr(char **arr);
char **dup_double_arr_sel(char **arr, int a, int b);
int add_node_pipe(pipes_t **head, pipes_t *node);
char *get_full_pipe_path(params_t *myshell, char *command);
int find_begin(char **user_input, int i);

char ***parse_space(char **commands, int i, params_t *myshell,
    char delimiter);
char ***parse_glue(params_t *myshell, char delimiter);
int fill_final_commands(char *all,
    char ***final_commands, params_t *myshell, char delimiter);

char **parse_space_individual(int i, params_t *myshell,
    char delimiter);


// COMMAND
void run_command(params_t *myshell);
void my_fork(params_t *myshell, char *command_path);
void handle_fork_errors(params_t *myshell);
char *find_path(char **parsed_paths, char *user_input, int j);


// PIPE
int exec_pipeline(params_t *myshell);
void exec_pipe(char ***commands_pipe, params_t *myshell);
void fork_pipe(params_t *myshell, char ***commands_pipe,
    char **commands_path);
void fork_pipes_2(params_t *myshell, pipes_t **pipes);

// REDIRECTIONS
int check_redirections(params_t *myshell);
void exec_redirect_space_r(params_t *myshell, params_t *subshell,
    int index, int i);
void exec_redirect_glue_r(params_t *myshell, params_t *subshell);
void exec_redirect_space_l(params_t *myshell, params_t *subshell,
    int index, int i);
void exec_redirect_glue_l(params_t *myshell, params_t *subshell);
void fork_redirections(params_t *subshell);
char *run_command_redirection(params_t *subshell);


#endif

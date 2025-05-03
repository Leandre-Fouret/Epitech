/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** fork_redirections
*/

#include "minish.h"
#include <stdio.h>
#include <string.h>

static int open_file(params_t *subshell)
{
    int fd = 0;

    if (subshell->redirect_type == 1)
        fd = open(subshell->user_input[1][0],
            O_CREAT | O_RDWR | O_TRUNC, 00400 | 00200);
    if (subshell->redirect_type == 2)
        fd = open(subshell->user_input[1][0],
            O_CREAT | O_RDWR | O_APPEND, 00400, 00200);
    return fd;
}

static void fork_right_redirection(params_t *subshell)
{
    pid_t pid = -1;
    int og_out = -1;
    int fd = open_file(subshell);

    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0) {
        og_out = dup(1);
        dup2(fd, 1);
        if (!run_builtins(subshell))
            run_command(subshell);
        exit(1);
    }
    close(fd);
    dup2(og_out, 1);
    waitpid(pid, &(subshell->status), 0);
}

static void fork_left(params_t *subshell)
{
    pid_t pid = -1;
    int og_in = -1;
    int fd = -1;

    fd = open(subshell->user_input[1][0], O_RDONLY);
    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0) {
        og_in = dup(0);
        dup2(fd, 0);
        if (!run_builtins(subshell))
            run_command(subshell);
        exit(1);
    }
    close(fd);
    dup2(og_in, 0);
    waitpid(pid, &(subshell->status), 0);
}

static void get_input(params_t *subshell, int heredoc_pipe[2])
{
    size_t len = 0;
    char *line = NULL;

    while (1) {
        write(1, "?  ", 3);
        if (getline(&line, &len, stdin) <= 0)
            break;
        if (my_strncmp(line, subshell->user_input[1][0],
            my_strlen(subshell->user_input[1][0])) == 0)
            break;
        write(heredoc_pipe[1], line, my_strlen(line));
        free(line);
        line = NULL;
    }
}

static void exec_heredoc_fork(params_t *subshell)
{
    int heredoc_pipe[2] = {0};

    pipe(heredoc_pipe);
    get_input(subshell, heredoc_pipe);
    close(heredoc_pipe[1]);
    dup2(heredoc_pipe[0], 0);
    close(heredoc_pipe[0]);
    subshell->command_path = run_command_redirection(subshell);
    if (subshell->command_path != NULL)
        execve(subshell->command_path, subshell->user_input[0],
            subshell->envp);
    exit(1);
}

static void fork_left_heredoc(params_t *subshell)
{
    pid_t pid = -1;

    pid = fork();
    if (pid == -1)
        return;
    if (pid == 0) {
        exec_heredoc_fork(subshell);
        if (subshell->command_path != NULL)
            free(subshell->command_path);
    }
    waitpid(pid, &(subshell->status), 0);
}

static void get_in_from_file(params_t *subshell)
{
    if (access(subshell->user_input[1][0], F_OK) != 0) {
        my_puterr(subshell->user_input[1][0]);
        my_puterr(": No such file or directory.\n");
        subshell->exit_code = 1;
        return;
    }
    fork_left(subshell);
}

void fork_redirections(params_t *subshell)
{
    if (subshell->redirect_type == 1 ||
        subshell->redirect_type == 2)
        fork_right_redirection(subshell);
    if (subshell->redirect_type == 3)
        get_in_from_file(subshell);
    if (subshell->redirect_type == 4) {
        fork_left_heredoc(subshell);
    }
}

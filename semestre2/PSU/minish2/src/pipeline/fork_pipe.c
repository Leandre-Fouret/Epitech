/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** fork_pipe
*/

#include "minish.h"

static void redirect_execution(params_t *myshell, pipes_t *current,
    int *prev_pipe_fd, int pipe_fds[2])
{
    if (*prev_pipe_fd != -1) {
        dup2(*prev_pipe_fd, 0);
        close(*prev_pipe_fd);
    }
    if (current->next != NULL) {
        dup2(pipe_fds[1], 1);
        close(pipe_fds[1]);
    }
    close(pipe_fds[0]);
    execve(current->command_path, current->command, myshell->envp);
    exit(1);
}

static void handle_child_process(params_t *myshell,
    pipes_t *current, int *prev_pipe_fd)
{
    pid_t pid = -1;
    int pipe_fds[2] = {-1};

    pipe(pipe_fds);
    pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0) {
        redirect_execution(myshell, current, prev_pipe_fd, pipe_fds);
    } else {
        close(pipe_fds[1]);
        if (*prev_pipe_fd != -1)
            close(*prev_pipe_fd);
        *prev_pipe_fd = pipe_fds[0];
    }
}

void execute_child_processes_2(params_t *myshell, pipes_t **pipes)
{
    pipes_t *current = *pipes;
    int prev_pipe_fd = -1;

    while (current != NULL) {
        handle_child_process(myshell, current, &prev_pipe_fd);
        current = current->next;
    }
    if (prev_pipe_fd != -1)
        close(prev_pipe_fd);
    current = *pipes;
    while (current != NULL) {
        wait(NULL);
        current = current->next;
    }
}

static int fork_localpath_error_2(params_t *myshell, pipes_t **pipes)
{
    int error = 0;
    pipes_t *current = *pipes;

    for (; current != NULL; current = current->next) {
        if (access(current->command_path, F_OK) == -1) {
            my_puterr(current->command_path);
            my_puterr(": Command not found.\n");
            error = 1;
        }
    }
    if (error) {
        myshell->exit_code = 1;
        myshell->status = 1;
    }
    return error;
}

void fork_pipes_2(params_t *myshell, pipes_t **pipes)
{
    if (fork_localpath_error_2(myshell, pipes))
        return;
    if (*pipes != NULL) {
        (*pipes)->read_end = -1;
        (*pipes)->write_end = -1;
    }
    execute_child_processes_2(myshell, pipes);
}

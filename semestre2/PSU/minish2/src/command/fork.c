/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** fork
*/

#include "minish.h"

static int fork_exceptions(params_t *myshell)
{
    int index = myshell->command_index;

    if ((my_strcmp(myshell->user_input[index][0], "ls") == 0) &&
        myshell->status != 0) {
        myshell->exit_code = 2;
        return 1;
    }
    return 0;
}

static void handle_core_dump(params_t *myshell)
{
    if (myshell->status != 0 && WCOREDUMP(myshell->status) &&
        myshell->status != -1) {
        my_printf("%s (core dumped)\n",
            strsignal(WTERMSIG(myshell->status)));
        myshell->exit_code = 139;
    }
    if (myshell->status != 0 && !WCOREDUMP(myshell->status)) {
        my_printf("%s\n",
            strsignal(WTERMSIG(myshell->status)));
        myshell->exit_code = 139;
    }
}

static void handle_wrong_local_exec(params_t *myshell)
{
    struct stat sb;
    int is_local = 0;
    int index = myshell->command_index;

    for (int i = 0; i < my_strlen(myshell->user_input[index][0]); i++)
        if (myshell->user_input[index][0][i] == '/')
            is_local = 1;
    lstat(myshell->user_input[index][0], &sb);
    if (sb.st_mode != 16877 && is_local)
        my_printf("%s: Exec format error. Binary file not executable.\n",
            myshell->user_input[index][0]);
    if (sb.st_mode == 16877 && is_local)
        my_printf("%s: Permission denied.\n",
            myshell->user_input[index][0]);
}

void handle_fork_errors(params_t *myshell)
{
    if (fork_exceptions(myshell))
        return;
    if (myshell->status == 256) {
        handle_wrong_local_exec(myshell);
        myshell->exit_code = 1;
        return;
    }
    if (myshell->status == 136) {
        my_printf("Floating exception (core dumped)\n");
        myshell->exit_code = 136;
        return;
    }
    handle_core_dump(myshell);
}

void my_fork(params_t *myshell, char *command_path)
{
    pid_t pid = 0;

    if (access(command_path, F_OK) == -1) {
        my_printf("%s: Command not found.\n", command_path);
        myshell->exit_code = 1;
        myshell->status = 1;
        return;
    }
    pid = fork();
    if (pid == -1)
        perror("fork");
    if (pid == 0) {
        if (execve(command_path, myshell->user_input[myshell->command_index],
            myshell->envp) == -1)
            exit(1);
    } else
        waitpid(pid, &(myshell->status), 0);
}

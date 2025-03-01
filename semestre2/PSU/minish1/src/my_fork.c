/*
** EPITECH PROJECT, 2025
** minish1
** File description:
** my_fork
*/

#include "minish.h"

/**
 * @brief Execute a program in a child process
 * @param *path The absolute path of the command to execute
 * @param ***tab_fork A tab of double arrays whith settings for execution
 * @param *status The status of the execution of the command
 */
void my_fork(char *path, char ***tab_fork, int *status)
{
    pid_t pid;

    if (access(path, F_OK) == -1) {
        my_printf("%s: Command not found.\n", path);
        *status = 1;
        return;
    }
    pid = fork();
    switch (pid) {
    case -1:
        perror("fork");
        break;
    case 0:
        *status = execve(path, tab_fork[0], tab_fork[1]);
        kill(getpid(), WTERMSIG(*status));
        break;
    default:
        waitpid(pid, status, 0);
        break;
    }
}

/**
 * @brief Free several settings that were needed for execution
 * @param *path The absolute path of the command executed
 * @param ***tab_fork The table of settings for the execution
 */
void free_command_related(char *path, char ***tab_fork)
{
    free(path);
    for (int i = 0; tab_fork[1][i] != NULL; i++)
        free(tab_fork[1][i]);
    free(tab_fork[1]);
    for (int i = 0; tab_fork[0][i] != NULL; i++)
        free(tab_fork[0][i]);
    free(tab_fork[0]);
}

int fork_exceptions(char ***tab_fork, int *status, char *path)
{
    if ((my_strcmp(tab_fork[0][0], "ls") == 0) && *status != 0) {
        *status = 2;
        free_command_related(path, tab_fork);
        return 1;
    }
    if (my_strncmp("exit", tab_fork[0][0], 4) == 0) {
        *status = 1;
        free_command_related(path, tab_fork);
        return 1;
    }
    return 0;
}

static void handle_core_dump(int *status, int *return_status)
{
    if (*status != 0 && WCOREDUMP(*status) && *status != -1) {
        my_printf("%s (core dumped)\n",
            strsignal(WTERMSIG(*status)));
        }
    if (*status != 0 && !WCOREDUMP(*status)) {
        my_printf("%s\n",
            strsignal(WTERMSIG(*status)));
        *return_status = 139;
    }
}

static void handle_wrong_local_exec(char ***tab_fork)
{
    struct stat sb;

    lstat(tab_fork[0][0], &sb);
    if (sb.st_mode != 16877)
        my_printf("%s: Exec format error. Binary file not executable.\n",
            tab_fork[0][0]);
    if (sb.st_mode == 16877)
        my_printf("%s: Permission denied.\n",
            tab_fork[0][0]);
}

void handle_fork_errors(char ***tab_fork, int *status, char *path,
    int *return_status)
{
    if (fork_exceptions(tab_fork, status, path))
        return;
    if (*status == 256) {
        handle_wrong_local_exec(tab_fork);
        *return_status = 50;
        return;
    }
    free_command_related(path, tab_fork);
    if (*status == 136) {
        my_printf("Floating exception (core dumped)\n");
        *return_status = 136;
        return;
    }
    handle_core_dump(status, return_status);
}

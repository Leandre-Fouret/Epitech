/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** cd
*/

#include "minish.h"

static int change_user_directory(char *dir, char *current_previous)
{
    int result = 0;
    char *stored = malloc(sizeof(char) * MAX_INPUT_SIZE);

    if (stored == NULL)
        return 1;
    stored[0] = 0;
    getcwd(stored, MAX_INPUT_SIZE);
    result = chdir(dir);
    if (result == 0) {
        my_strcpy(current_previous, stored);
        free(stored);
        return 0;
    }
    free(stored);
    my_printf("%s: %s.\n", dir, strerror(errno));
    return 1;
}

static void interpret_user_dir(params_t *myshell, int *out)
{
    int result = 0;
    int index = myshell->command_index;

    myshell->cd.tmp_home = my_strdup(myshell->user_input[index][1]);
    my_strcpy(myshell->user_input[index][1], "/home/");
    my_strcat(myshell->user_input[index][1], myshell->cd.tmp_home + 1);
    result = access(myshell->user_input[index][1], F_OK);
    if (result == 0) {
        *out = change_user_directory(myshell->user_input[index][1],
            myshell->current_previous);
    }
    if (result != 0) {
        my_printf("Unknown user: %s.\n", myshell->cd.tmp_home + 1);
        *out = 1;
    }
}

static int change_directory(params_t *myshell)
{
    int result = 0;
    char *stored = malloc(sizeof(char) * MAX_INPUT_SIZE);
    int index = myshell->command_index;

    if (stored == NULL)
        return 1;
    stored[0] = 0;
    getcwd(stored, MAX_INPUT_SIZE);
    result = chdir(myshell->cd.current_dir);
    if (result == 0) {
        my_strcpy(myshell->current_previous, stored);
        free(stored);
        return 0;
    }
    my_printf("%s: %s.\n", myshell->user_input[index][1], strerror(errno));
    free(stored);
    return 1;
}

static int change_to_home(params_t *myshell, int *out)
{
    int moved = 0;
    int index = myshell->command_index;

    if (my_strncmp(myshell->user_input[index][1], "~/", 2) == 0 ||
        my_strncmp(myshell->user_input[index][1], "~\0", 2) == 0) {
        if (myshell->cd.home == NULL) {
            return 1;
        }
        my_strcpy(myshell->cd.current_dir, myshell->cd.home);
        moved = 1;
        *out = change_directory(myshell);
    } else if (myshell->user_input[index][1][0] == '~') {
        interpret_user_dir(myshell, out);
        moved = 1;
    }
    return moved;
}

static int change_to_previous(params_t *myshell)
{
    char *stored = NULL;
    int index = myshell->command_index;

    if (my_strncmp(myshell->user_input[index][1], "-\0", 2) == 0) {
        if (myshell->cd.home == NULL) {
            return 1;
        }
        stored = my_strdup(myshell->current_previous);
        getcwd(myshell->current_previous, MAX_INPUT_SIZE);
        chdir(stored);
        free(stored);
        return 1;
    }
    return 0;
}

static int interpret_cd(params_t *myshell)
{
    int moved = 0;
    int out = 0;
    int index = myshell->command_index;

    moved = change_to_home(myshell, &out);
    if (!moved)
        moved = change_to_previous(myshell);
    if (myshell->user_input[index][1][0] != '/' && !moved) {
        my_strcat(myshell->cd.current_dir, myshell->user_input[index][1]);
        out = change_directory(myshell);
    }
    if (myshell->user_input[index][1][0] == '/' && !moved){
        free(myshell->cd.current_dir);
        myshell->cd.current_dir = my_strdup(myshell->user_input[index][1]);
        out = change_directory(myshell);
    }
    return out;
}

void my_cd(params_t *myshell)
{
    env_t *current = *(myshell->head);
    int index = myshell->command_index;

    myshell->cd.home = NULL;
    myshell->cd.tmp_home = NULL;
    myshell->cd.current_dir = malloc(sizeof(char) * MAX_INPUT_SIZE);
    myshell->cd.new_dir = malloc(sizeof(char) * MAX_INPUT_SIZE);
    for (; current != NULL; current = current->next)
        if (my_strcmp("HOME", current->key) == 0 && current->value != NULL)
            myshell->cd.home = my_strdup(current->value);
    if (myshell->cd.current_dir == NULL || myshell->cd.new_dir == NULL)
        return;
    myshell->cd.current_dir[0] = 0;
    myshell->cd.new_dir[0] = 0;
    myshell->cd.current_dir = getcwd(myshell->cd.current_dir, MAX_INPUT_SIZE);
    my_strcat(myshell->cd.current_dir, "/");
    if (myshell->user_input[index][1] != NULL)
        myshell->exit_code = interpret_cd(myshell);
    else
        chdir(myshell->cd.home);
}

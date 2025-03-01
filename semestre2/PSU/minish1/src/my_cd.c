/*
** EPITECH PROJECT, 2025
** MiniShell1
** File description:
** Contains all the cd functions
*/

/**
 * @file my_cd.c
 * @brief All the functions that execute the 'cd' built-in command
 *
 * The cd is the "change directory" command. It allows the user to change
 * its position in the computer and to freely browse it.
 */

#include "minish.h"

/**
  * @brief Extract the given path from the whole user input command
  * @param *new_dir Buffer in which to put the path
  * @param *user_input The whole entered command to parse
  */
static void parse_path(char *new_dir, char *user_input)
{
    int i = 0;
    int j = 0;

    for (; user_input[i] != 0; i++)
        if (user_input[i] == ' ')
            break;
    i++;
    for (; user_input[i] != 0; j++) {
        new_dir[j] = user_input[i];
        i++;
    }
    new_dir[j] = 0;
}

/**
  * @brief Changes the current user directory
  * @param *dir The new working dir absolute path
  * @param *lonely The new directory relative path
  */
static int change_user_directory(char *dir, char *current_previous)
{
    int result = 0;
    char *stored = malloc(sizeof(char) * STRING_SIZE);

    if (stored == NULL)
        return 1;
    stored[0] = 0;
    getcwd(stored, STRING_SIZE);
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

/**
  * @brief Assembles, checks, and changes the user dir
  * @param *tmp_home The parsed path in the command
  * @param *new_dir The buffer where to put the new dir absolute path
  * @param *moved A boolean to indicate if a change of dir occured
  */
static void interpret_user_dir(char *tmp_home, char *new_dir, int *out,
    char *current_previous)
{
    int result = 0;

    tmp_home = my_strdup(new_dir);
    my_strcpy(new_dir, "/home/");
    my_strcat(new_dir, tmp_home + 1);
    result = access(new_dir, F_OK);
    if (result == 0) {
        *out = change_user_directory(new_dir, current_previous);
    }
    if (result != 0) {
        my_printf("Unknown user: %s.\n", tmp_home + 1);
        *out = 1;
    }
}

/**
  * @brief Changes the current working directory
  * @param *dir The new working dir absolute path
  * @param *lonely The new directory relative path
  */
static int change_directory(char *dir, char *lonely, char *current_previous)
{
    int result = 0;
    char *stored = malloc(sizeof(char) * STRING_SIZE);

    if (stored == NULL)
        return 1;
    stored[0] = 0;
    getcwd(stored, STRING_SIZE);
    result = chdir(dir);
    if (result == 0) {
        my_strcpy(current_previous, stored);
        free(stored);
        return 0;
    }
    my_printf("%s: %s.\n", lonely, strerror(errno));
    free(stored);
    return 1;
}

/**
  * @brief Free all the allocated variables relative to the cd command
  * @param *home The home absolute path to free
  * @param *curr_dir The old directory path to free
  * @param *new_dir The new directory path to free
  * @param *tmp_home The path following the '~'
  */
static void free_cd(char **tab_cd, char *new_dir)
{
    free(tab_cd[0]);
    free(tab_cd[1]);
    free(tab_cd[2]);
    free(new_dir);
}

static int change_to_home(char **tab_cd, int *out, char *current_previous)
{
    int moved = 0;

    if (my_strncmp(tab_cd[3], "~/", 2) == 0 ||
        my_strncmp(tab_cd[3], "~\0", 2) == 0) {
        if (tab_cd[0] == NULL) {
            free_cd(tab_cd, NULL);
            return 1;
        }
        tab_cd[1] = my_strdup(tab_cd[3]);
        my_strcpy(tab_cd[3], tab_cd[0]);
        my_strcat(tab_cd[3], tab_cd[1] + 1);
        moved = 1;
        *out = change_directory(tab_cd[3], tab_cd[3], current_previous);
    } else if (tab_cd[3][0] == '~') {
        interpret_user_dir(tab_cd[1], tab_cd[3], out, current_previous);
        moved = 1;
    }
    return moved;
}

static int change_to_previous(char **tab_cd, char *current_previous)
{
    char *stored = NULL;

    if (my_strncmp(tab_cd[3], "-\0", 2) == 0) {
        if (tab_cd[0] == NULL) {
            free_cd(tab_cd, NULL);
            return 1;
        }
        stored = my_strdup(current_previous);
        getcwd(current_previous, STRING_SIZE);
        chdir(stored);
        free(stored);
        return 1;
    }
    return 0;
}

/**
  * @brief Analyze the enetered path and change the current dir from it
  * @param *home The home path (env variable)
  * @param *tmp_home The path following the '~' character
  * @param *curr_dir The current working directory
  * @param *new_dir The new directory we want to go in
  */
static int interpret_cd(char **tab_cd, char *current_previous)
{
    int moved = 0;
    int out = 0;

    moved = change_to_home(tab_cd, &out, current_previous);
    if (!moved)
        moved = change_to_previous(tab_cd, current_previous);
    if (tab_cd[3][0] != '/' && !moved) {
        my_strcat(tab_cd[2], tab_cd[3]);
        out = change_directory(tab_cd[2], tab_cd[3], current_previous);
    }
    if (tab_cd[3][0] == '/' && !moved){
        out = change_directory(tab_cd[3], tab_cd[3], current_previous);
    }
    return out;
}

//tab_cd = home, tmp_home, curr_dir, new_dir
/**
  * @brief Change the current directoy if the host
  * @param *user_input To know the path to go to
  * @param **head The linked list with the env variables
  */
int my_cd(char *user_input, env_linked_t **head, char *current_previous)
{
    env_linked_t *current = *head;
    int out = 0;
    char *tab_cd[4] = {NULL, NULL, malloc(sizeof(char) * STRING_SIZE),
        malloc(sizeof(char) * STRING_SIZE)};

    for (; current != NULL; current = current->next)
        if (my_strcmp("HOME", current->key) == 0 && current->value != NULL)
            tab_cd[0] = my_strdup(current->value);
    if (tab_cd[2] == NULL || tab_cd[3] == NULL)
        return 1;
    tab_cd[2][0] = 0;
    tab_cd[3][0] = 0;
    tab_cd[2] = getcwd(tab_cd[2], STRING_SIZE);
    my_strcat(tab_cd[2], "/");
    parse_path(tab_cd[3], user_input);
    out = interpret_cd(tab_cd, current_previous);
    free_cd(tab_cd, tab_cd[3]);
    return out;
}

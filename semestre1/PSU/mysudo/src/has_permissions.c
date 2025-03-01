/*
** EPITECH PROJECT, 2025
** has_permissions
** File description:
** checking sudoers
*/

/**
 * @file hash_permissions.c
 * @brief Check if a user is in the sudoers file
 *
 * Contains the function check if a user is in the sudoers file.
 * Also handle the check of groups in the sudoers file
 */

#include "../include/my_sudo.h"

/**
 * @brief Manually add the user main group to the group of groups
 *
 * @param *group_count The number of groups of the user
 * @param *groups[] An array which contains all the groups of the user
 * @param *username The username
 * @param *line the analyzed line from the /etc/group file
 * @return void
 */
void add_group(int *group_count, char *groups[], char *username, char *line)
{
    char *group_name = strtok(line, ":");
    char *group_members = NULL;

    strtok(NULL, ":");
    strtok(NULL, ":");
    group_members = strtok(NULL, ":");
    if ((group_members && strstr(group_members, username))
        || (group_name && strcmp(group_name, username) == 0)) {
        groups[*group_count] = strdup(group_name);
        (*group_count)++;
    }
}

/**
 * @brief Get the user groups
 *
 * @param *username The username to know which groups to focus on
 * @param *groups[] The double array in which to store the groups names
 * @param *group_count The number of groups to increment for each group
 * @return int A status code
 */
int get_user_groups(char *username, char *groups[], int *group_count)
{
    FILE *group_file = fopen("/etc/group", "r");
    char line[MAX_LINE_LENGTH];

    if (!group_file) {
        perror("Opening /etc/group failed\n");
        return 0;
    }
    while (fgets(line, sizeof(line), group_file))
        add_group(group_count, groups, username, line);
    fclose(group_file);
    return 1;
}

/**
 * @brief Free the list of groups
 *
 * @param groups_count The number of groups
 * @param **groups The double array that contains all the groups names
 * @param return_value A status code to return at the end of the function
 * @return int A status code
 */
static int free_group_list(int group_count, char **groups, int return_value)
{
    for (int i = 0; i < group_count; i++)
        free(groups[i]);
    return return_value;
}

int check_if_in_sudoers(char *line, char **groups,
    int group_count, char *username)
{
    if (line[0] == '#' || line[0] == '\n')
        return 0;
    if (strstr(line, username))
        return free_group_list(group_count, groups, 1);
    for (int i = 0; i < group_count; i++) {
        if (strstr(line, groups[i]))
            return free_group_list(group_count, groups, 1);
    }
    return 0;
}

/**
 * @brief Chech if a user has the sudoers permissions
 *
 * @param *username The username to check
 * @return int A boolean to know if yes or no
 */
int has_sudo_permissions(char *username)
{
    char *groups[MAX_GROUPS];
    int group_count = 0;
    FILE *sudoers = fopen("/etc/sudoers", "r");
    char line[1024];

    if (!get_user_groups(username, groups, &group_count))
        return 0;
    if (!sudoers) {
        perror("Opening /etc/sudoers failed\n");
        return free_group_list(group_count, groups, 0);
    }
    while (fgets(line, sizeof(line), sudoers)) {
        if (check_if_in_sudoers(line, groups, group_count, username) == 1) {
            fclose(sudoers);
            return 1;
        }
    }
    fclose(sudoers);
    return free_group_list(group_count, groups, 0);
}

/**
 * @brief Check prealable condition before check sudoers file
 *
 * @param *username The username to check
 * @return int A status code
 */
int checks_permissions(char *username)
{
    if (strcmp(username, "root") != 0) {
        if (has_sudo_permissions(username) == 0) {
            dprintf(2, "%s is not in the sudoers file\n", username);
            return 84;
        }
    }
    return 0;
}

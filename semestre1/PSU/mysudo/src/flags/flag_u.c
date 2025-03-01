/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** Handle the u flag
*/

/**
 * @file flag_u.c
 * @brief Execute the u flag
 *
 * The u flag is supposed to make the username become another user
 */

#include "../../include/my_sudo.h"

void add_group_id(int *group_count, gid_t *groups, char *username, char *line)
{
    char *group_name = strtok(line, ":");
    char *group_members = NULL;
    char *group_ids = NULL;
    gid_t temporary;

    strtok(NULL, ":");
    group_ids = strtok(NULL, ":");
    group_members = strtok(NULL, ":");
    if (!group_name || !group_members || !group_ids)
        return;
    if (strstr(group_members, username)) {
        groups[*group_count] = (gid_t)atoi(group_ids);
        (*group_count)++;
    }
    if (strcmp(group_name, username) == 0) {
        temporary = groups[0];
        groups[0] = (gid_t)atoi(group_ids);
        groups[*group_count] = temporary;
        (*group_count)++;
    }
}

gid_t *get_user_groups_ids(char *username, int *group_count)
{
    static gid_t groups_id[MAX_GROUPS];
    FILE *group_file = fopen("/etc/group", "r");
    char line[MAX_LINE_LENGTH];

    if (!group_file) {
        perror("Opening /etc/group failed");
        return NULL;
    }
    *group_count = 0;
    while (fgets(line, sizeof(line), group_file) && *group_count < MAX_GROUPS)
        add_group_id(group_count, groups_id, username, line);
    fclose(group_file);
    return groups_id;
}

void search_uid(char *uid, char *gid, char *username, FILE *file)
{
    char line[STRING_SIZE];
    char file_uid[STRING_SIZE];
    char file_username[STRING_SIZE];
    char file_gid[STRING_SIZE];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%[^:]:%[^:]:",
            file_username, file_uid, file_gid) != 3)
            continue;
        if (strcmp(username, file_username) == 0) {
            strncpy(uid, file_uid, STRING_SIZE);
            uid[STRING_SIZE - 1] = '\0';
            strncpy(gid, file_gid, STRING_SIZE);
            gid[STRING_SIZE - 1] = '\0';
            fclose(file);
            return;
        }
    }
    fclose(file);
    strcpy(uid, "-1");
}

int change_user(char *username)
{
    char *uid = malloc(STRING_SIZE);
    char *gid = malloc(STRING_SIZE);
    FILE *file = fopen("/etc/passwd", "r");
    int group_count = 0;
    gid_t *groups_id = get_user_groups_ids(username, &group_count);

    if (!uid || !file || !groups_id || !gid) {
        perror("malloc or opening /etc/passwd failed");
        free(uid);
        if (file)
            fclose(file);
        return 84;
    }
    search_uid(uid, gid, username, file);
    if (set_id_and_groups(uid, gid, group_count, groups_id) == 84) {
        free(uid);
        return 84;
    }
    free(uid);
    return 0;
}

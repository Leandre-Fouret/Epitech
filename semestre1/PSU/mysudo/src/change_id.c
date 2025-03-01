/*
** EPITECH PROJECT, 2025
** change_id
** File description:
** changing id for flags u and g
*/

/**
 * @file change_id.c
 * @brief Change all the ids
 *
 * Necessary for the sudo function to work well
 */

#include "../include/my_sudo.h"

/**
 * @brief Set the root ids
 *
 * @return void
 */
void set_root(void)
{
    setgid((uid_t)0);
    setuid((uid_t)0);
    seteuid((uid_t)0);
    setegid((gid_t)0);
}

/**
 * @brief Set the right ids
 *
 * @param *uid uid to set
 * @param *gid gid to set
 * @param group_count The number of groups
 * @param *groups_id A structure that contains infos on groups
 * @return int A status code
 */
int set_id_and_groups(char *uid, char *gid, int group_count, gid_t *groups_id)
{
    int uid_to_set = atoi(uid);
    int gid_to_set = atoi(gid);

    if (strcmp(uid, "-1") != 0) {
        setgroups(0, NULL);
        setgid((gid_t)gid_to_set);
        setuid((uid_t)uid_to_set);
        setgroups(group_count, groups_id);
        return 0;
    }
    return 84;
}

/**
 * @brief Get the gid of a group with a given groupname
 *
 * @param *groupname The given groupname
 * @return gid_t The structure with all the informations
 */
gid_t get_group_gid(const char *groupname)
{
    FILE *file = fopen("/etc/group", "r");
    char line[MAX_LINE_LENGTH];
    char file_groupname[STRING_SIZE];
    char file_gid[STRING_SIZE];
    gid_t gid;

    if (!file)
        return -1;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%*[^:]:%[^:]:", file_groupname, file_gid) != 2)
            continue;
        if (strcmp(groupname, file_groupname) == 0) {
            gid = (gid_t)atoi(file_gid);
            fclose(file);
            return gid;
        }
    }
    fclose(file);
    return -1;
}

/**
 * @brief Set the correct gids
 *
 * @param *groupname The groupname to set the correct gid
 * @param *username The username to get the correct groups name
 * @return int A status code
 */
int change_group(char *groupname, char *username)
{
    char *groups_username[MAX_GROUPS];
    int group_count_user = 0;
    gid_t gid_group = get_group_gid(groupname);

    if ((int)gid_group == -1 ||
        !get_user_groups(username, groups_username, &group_count_user)) {
        dprintf(2, "my_sudo: unknown group %s\n", groupname);
        return 84;
    }
    for (int i = 0; i < group_count_user; i++) {
        if (strcmp(groups_username[i], groupname) == 0
            || strcmp(username, "root") == 0) {
            setgid(gid_group);
            return 0;
        }
    }
    dprintf(2, "Sorry, user %s is not allowed to execute this command "
        "as %s:%s on ubuntu.\n", username, username, groupname);
    return 84;
}

/**
 * @brief Main function to change the id
 *
 * @param flags The structure whith infos on the flags
 * @param *username The username to get all the correct informations
 * @return void
 */
int change_ids(flags_t flags, char *username)
{
    char *user_to_be = username;

    if (flags.u) {
        if (change_user(flags.username) == 84) {
            dprintf(2, "my_sudo: unknown user %s\n", flags.username);
            return 84;
        }
        user_to_be = flags.username;
    }
    if (!flags.u)
        set_root();
    if (flags.g) {
        if (change_group(flags.group_name, user_to_be) == 84)
            return 84;
    }
    return 0;
}

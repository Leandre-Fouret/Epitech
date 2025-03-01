/*
** EPITECH PROJECT, 2025
** my_radar_h
** File description:
** contains all structs and functions prototypes
*/

#ifndef MY_SUDO_H_
    #define MY_SUDO_H_
    #include <stdio.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdlib.h>
    #include <crypt.h>
    #include <termios.h>
    #include <grp.h>
    #include <sys/types.h>
    #define STRING_SIZE 256
    #define LINE_SIZE 512
    #define MAX_GROUPS 256
    #define MAX_LINE_LENGTH 1024

//STRUCTS

typedef struct flags {
    bool u;
    char *username;
    bool E;
    bool g;
    char *group_name;
    bool s;
    int problem;
} flags_t;

//LIB

int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n, int k);
char **my_str_to_word_array(char const *str);
char *turns_int_to_string(int nb);
int my_strlen(char const *str);
int str_toi(const char *str);
char *my_strcat(char *dest, char const *src);

// my_sudo functions

char *turns_int_to_string(int nb);
char *get_username(char *uid);
char *get_hash(char *username);
char *get_salt(char *hash);
void disable_echo(void);
void enable_echo(void);
int search_for_flags(int argc, char **argv, flags_t *flags);
int has_sudo_permissions(char *username);
int sanitize_environment(char *username);
void spawn_shell(char *shell);
int change_user(char *username);
int sanitize_without_e(char *username);
int change_ids(flags_t flags, char *username);
int set_id_and_groups(char *uid, char *gid, int group_count, gid_t *groups_id);
gid_t *get_user_groups_ids(char *username, int *group_count);
int checks_permissions(char *username);
int get_user_groups(char *username, char *groups[], int *group_count);

#endif /* !MY_SUDO_H_ */

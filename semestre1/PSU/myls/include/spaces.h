/*
** EPITECH PROJECT, 2024
** spaces
** File description:
** structures for folder and file buffers
*/

//Flags are : a l R d r t

#ifndef MYLS
    #define MYLS

typedef struct spaces_s {
    char **global_folder_space;
    int folder_index;
    char **global_file_space;
    int file_index;
    int *flags;
} spaces_t;

typedef struct filetype_s {
    mode_t bitmask;
    int (*function)(char const *pathname, spaces_t *storage, char *str);
    char *description;
} filetype_t;

int put_in_file_buffer(char const *pathname, spaces_t *storage, char *str);
int put_in_folder_buffer(char const *pathname, spaces_t *storage, char *str);
int tmp_putstr(char const *pathname, spaces_t *storage, char *str);
int open_folder(char const *pathname, int ac, int *flags_storage);
int double_array_len(char **tab);
int info_file(char const *pathname, spaces_t *storage);
void find_flags(char **av, spaces_t *storage);
void display_flags(spaces_t *storage);
void output_flags(int *flags_storage, struct dirent *entry);
void get_nb_file(int *nb_file, int ac, char **av);
int choose_which_file(char **av, int ac, int nb_file, spaces_t *storage);
void display_directories_names(spaces_t *storage);
void display_directories_content(spaces_t *storage, int ac);

#endif /* !MYLS */

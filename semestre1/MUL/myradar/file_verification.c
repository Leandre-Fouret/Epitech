/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** Verify and interpret the given config file
*/

#include "radar.h"

static int check_number(char *line, int *i, int *args_counter)
{
    int len = *i;
    char *num;
    int index = 0;

    for (; line[len] != ' ' && line[len] != '\n' && line[*i] != '\0'; len++);
    num = malloc(sizeof(char) * (len + 1));
    if (num == NULL)
        return 84;
    memset(num, 0, sizeof(char) * (len + 1));
    while (line[*i] != ' ' && line[*i] != '\n' && line[*i] != '\0') {
        num[index] = line[*i];
        (*i)++;
        index++;
    }
    for (int a = 0; num[a] != '\0'; a++)
        if (!my_isdigit(num[a]))
            return 84;
    (*args_counter)++;
    free(num);
    return 0;
}

static int look_for_digit(char *line, int *i, int *args_counter)
{
    if (my_isdigit(line[*i])) {
        if (check_number(line, i, args_counter) == 84)
            return 84;
    }
    return 0;
}

static int check_airplane(char *line)
{
    int args_counter = 0;
    int length = my_strlen(line);

    for (int i = 1; i < length; i++) {
        if (look_for_digit(line, &i, &args_counter) == 84)
            return 84;
    }
    if (args_counter != 6)
        return 84;
    return 0;
}

static int check_tower(char *line)
{
    int args_counter = 0;
    int length = my_strlen(line);

    for (int i = 1; i < length; i++) {
        if (look_for_digit(line, &i, &args_counter) == 84)
            return 84;
    }
    if (args_counter != 3) {
        return 84;
    }
    return 0;
}

static int check_line(char *line)
{
    if (*line != 'A' && *line != 'T')
        return 84;
    if (*line == 'A')
        if (check_airplane(line) == 84)
            return 84;
    if (*line == 'T')
        if (check_tower(line) == 84)
            return 84;
    return 0;
}

int verify_file(char *path)
{
    FILE *stream;
    size_t len = 0;
    int nread = 0;
    char *line = NULL;

    stream = fopen(path, "r");
    nread = getline(&line, &len, stream);
    while (nread != -1) {
        if (check_line(line) == 84)
            return 84;
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return 0;
}

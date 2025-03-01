/*
** EPITECH PROJECT, 2024
** top_bar
** File description:
** Everything about the uptime and users logged in
*/

#include "top.h"

int isnum(char *str)
{
    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

static void addstate(char *status_buff, int iterator, int *states)
{
    if (status_buff[iterator] == 'S' || status_buff[iterator] == 'D'
        || status_buff[iterator] == 'I' || status_buff[iterator] == 'P' ||
        status_buff[iterator] == 'K' || status_buff[iterator] == 'C'
        || status_buff[iterator] == 'W')
        states[1]++;
    if (status_buff[iterator] == 'R')
        states[0]++;
    if (status_buff[iterator] == 'T')
        states[2]++;
    if (status_buff[iterator] == 'Z')
        states[3]++;
}

static int find_state(char *absolutename, int *fd, char *status_buff,
    int *iterator)
{
    *fd = open(absolutename, O_RDONLY);
    if (*fd == -1) {
        return -1;
    }
    read(*fd, status_buff, 100);
    for (; status_buff[*iterator] != ' '; (*iterator)++);
    (*iterator)++;
    for (; status_buff[*iterator] != ' '; (*iterator)++);
    (*iterator)++;
    return 0;
}

static void getstate(char *dirname, int *states)
{
    int fd = 0;
    char *absolutename = malloc(sizeof(char) * (strlen(dirname) + 13));
    char *status_buff = malloc(sizeof(char) * 100);
    int iterator = 0;

    memset(absolutename, 0, sizeof(char) * (strlen(dirname) + 13));
    memset(status_buff, 0, sizeof(char) * 100);
    snprintf(absolutename, strlen(dirname) + 13, "/proc/%s/stat", dirname);
    if (find_state(absolutename, &fd, status_buff, &iterator) == -1)
        return;
    addstate(status_buff, iterator, states);
    free(absolutename);
    free(status_buff);
    if (fd != -1)
        close(fd);
}

void count_processes(void)
{
    DIR *process_fd;
    struct dirent *stream;
    int states[4] = {0, 0, 0, 0};

    process_fd = opendir("/proc");
    if (process_fd == NULL) {
        return;
    }
    stream = readdir(process_fd);
    while (stream != NULL) {
        if (isnum(stream->d_name))
            getstate(stream->d_name, states);
        stream = readdir(process_fd);
    }
    mvprintw(1, 0,
    "Tasks: %i total, %i running, %i sleeping, %i stopped, %i zombie",
        states[0] + states[1] + states[2] + states[3], states[0],
        states[1], states[2], states[3]);
    closedir(process_fd);
}

void logged_users(void)
{
    struct utmp current_user;
    int fd;
    int count = 0;

    fd = open("/var/run/utmp", O_RDONLY);
    if (fd == -1) {
        mvprintw(0, 30, "0 user, ");
        return;
    }
    while (read(fd, &current_user, sizeof(current_user)) ==
        sizeof(current_user))
        if (current_user.ut_type == USER_PROCESS)
            count++;
    if (fd != -1)
        close(fd);
    if (count > 1)
        mvprintw(0, 30, "%i users, ", count);
    if (count <= 1)
        mvprintw(0, 30, "%i user, ", count);
}

static void free_loadavg(char *buff, double *loadavg)
{
    free(buff);
    free(loadavg);
}

static void display_loadavg(double *loadavg, int *fd, char *buff)
{
    mvprintw(0, 40, "load average: ");
    if (loadavg[0] != 0.00)
        mvprintw(0, 55, "%.2f, ", loadavg[0]);
    if (loadavg[1] != 0.00)
        mvprintw(0, 61, "%.2f, ", loadavg[1]);
    if (loadavg[2] != 0.00)
        mvprintw(0, 67, "%.2f", loadavg[2]);
    free_loadavg(buff, loadavg);
    if (*fd != -1)
        close(*fd);
}

void my_getloadavg(int nelem)
{
    int fd = open("/proc/loadavg", O_RDONLY);
    char *buff = malloc(sizeof(char) * 100);
    double *loadavg = malloc(sizeof(double) * 3);

    memset(buff, 0, sizeof(char) * 100);
    memset(loadavg, 0, sizeof(char) * 3);
    if (fd == -1) {
        free_loadavg(buff, loadavg);
        return;
    }
    read(fd, buff, 14);
    for (int i = 0; i < nelem; i++) {
        if (atof(buff + i * 5) != 0.00)
            loadavg[i] = atof(buff + i * 5);
    }
    display_loadavg(loadavg, &fd, buff);
}

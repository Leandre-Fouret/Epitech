/*
** EPITECH PROJECT, 2024
** time
** File description:
** Functions to get the time in the top bar
*/

#include "top.h"

static void display_uptime(int days, int hours, int minutes, int *column)
{
    if (days > 0) {
        mvprintw(0, *column, "%02i days, ", days);
        *column += 6;
    }
    if (hours > 0) {
        mvprintw(0, *column, "%i:", hours);
        *column += 3;
    }
    if (hours == 0) {
        mvprintw(0, *column - 1, "%2i min", minutes);
        *column += 3;
    } else {
        mvprintw(0, *column - 1, "%02i,", minutes);
    }
}

static void convert_seconds(long totalSeconds)
{
    int days;
    int hours;
    int minutes;
    int column = 20;

    days = totalSeconds / (24 * 3600);
    totalSeconds %= (24 * 3600);
    hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    minutes = totalSeconds / 60;
    display_uptime(days, hours, minutes, &column);
}

static void display_current_time(time_t *temps, struct tm **timeinfo)
{
    time(temps);
    *timeinfo = localtime(temps);
    mvprintw(0, 6, "%d:%02d:%02d up ", (*timeinfo)->tm_hour,
        (*timeinfo)->tm_min, (*timeinfo)->tm_sec);
}

static int find_time(char *buff, char *subbuf, int *fd)
{
    if (*fd == -1) {
        free(buff);
        free(subbuf);
        return -1;
    }
    read(*fd, buff, 10);
    for (int i = 0; i < 10; i++) {
        if (buff[i] == '.')
            break;
        subbuf[i] = buff[i];
    }
    subbuf[strlen(subbuf)] = '\0';
    return 0;
}

void my_time(void)
{
    time_t temps;
    struct tm *timeinfo;
    char *buff = malloc(sizeof(char) * 10);
    char *subbuf = malloc(sizeof(char) * 10);
    int fd = open("/proc/uptime", O_RDONLY);

    memset(buff, 0, sizeof(char) * 10);
    memset(subbuf, 0, sizeof(char) * 10);
    if (find_time(buff, subbuf, &fd) == -1)
        return;
    free(buff);
    convert_seconds(atoi(subbuf));
    free(subbuf);
    display_current_time(&temps, &timeinfo);
}

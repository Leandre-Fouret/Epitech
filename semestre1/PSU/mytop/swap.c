/*
** EPITECH PROJECT, 2024
** swap
** File description:
** Swap line
*/

#include "top.h"

static void get_swaptotal(char *buff, double *swaptotal)
{
    int i = 14 * 28 + 12;
    char *swaptotalbuff = malloc(sizeof(char) * 20);
    int j = 0;

    memset(swaptotalbuff, 0, sizeof(char) * 20);
    if (swaptotalbuff == NULL)
        exit(84);
    for (; buff[i] == ' '; i++);
    for (; buff[i] != ' '; i++) {
        swaptotalbuff[j] = buff[i];
        j++;
    }
    mvprintw(4, 11, "%.1f total,", atof(swaptotalbuff) / 1000);
    *swaptotal = atof(swaptotalbuff) / 1000;
    free(swaptotalbuff);
}

static void get_swapfree(char *buff, double *swapfree)
{
    int i = 15 * 28 + 12;
    char *swapfreebuff = malloc(sizeof(char) * 20);
    int j = 0;

    memset(swapfreebuff, 0, sizeof(char) * 20);
    if (swapfreebuff == NULL)
        exit(84);
    for (; buff[i] == ' '; i++);
    for (; buff[i] != ' '; i++) {
        swapfreebuff[j] = buff[i];
        j++;
    }
    mvprintw(4, 25, "%.1f free,", atof(swapfreebuff) / 1000);
    *swapfree = atof(swapfreebuff) / 1000;
    free(swapfreebuff);
}

static void get_avail_mem(char *buff)
{
    int i = 2 * 28 + 15;
    char *availmembuff = malloc(sizeof(char) * 20);
    int j = 0;

    memset(availmembuff, 0, sizeof(char) * 20);
    if (availmembuff == NULL)
        exit(84);
    for (; buff[i] == ' '; i++);
    for (; buff[i] != ' '; i++) {
        availmembuff[j] = buff[i];
        j++;
    }
    mvprintw(4, 55, "%.1f avail Mem", atof(availmembuff) / 1000);
    free(availmembuff);
}

static void get_swapused(double *swaptotal, double *swapfree)
{
    mvprintw(4, 40, "%.1f used.", *swaptotal - *swapfree);
}

void swap_line(void)
{
    int fd = 0;
    char *buff = malloc(sizeof(char) * 27 * 17);
    double swaptotal;
    double swapfree;

    memset(buff, 0, sizeof(char) * 27 * 17);
    mvprintw(4, 0, "MiB Swap:");
    fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1)
        exit(84);
    read(fd, buff, 27 * 17);
    get_swaptotal(buff, &swaptotal);
    get_swapfree(buff, &swapfree);
    get_swapused(&swaptotal, &swapfree);
    get_avail_mem(buff);
    close(fd);
    free(buff);
}

/*
** EPITECH PROJECT, 2024
** cpu_column
** File description:
** function to get the cpu_column
*/

#include "top.h"

static void get_times(char *stat_file_buffer, char *time_a, char *time_b)
{
    int space_counter = 0;
    int i = 0;
    int j = 0;

    for (; space_counter < 13; i++)
        if (stat_file_buffer[i] == ' ')
            space_counter++;
    for (; stat_file_buffer[i] != ' ' && j < 9; i++) {
        time_a[j] = stat_file_buffer[i];
        j++;
    }
    time_a[j] = '\0';
    i++;
    j = 0;
    for (; stat_file_buffer[i] != ' ' && j < 9; i++) {
        time_b[j] = stat_file_buffer[i];
        j++;
    }
    time_b[j] = '\0';
}

void push_time(topinfo_t *new_process, char *stat_file_buffer)
{
    char *time_a = malloc(sizeof(char) * 10);
    char *time_b = malloc(sizeof(char) * 10);
    double result_time = 0;

    memset(time_a, 0, sizeof(char) * 10);
    memset(time_b, 0, sizeof(char) * 10);
    get_times(stat_file_buffer, time_a, time_b);
    result_time = ((atoi(time_a) + atoi(time_b)));
    new_process->time = result_time;
    free(time_a);
    free(time_b);
}

static long get_uptime(void)
{
    int fd = open("/proc/uptime", O_RDONLY);
    char *buff = malloc(sizeof(char) * 50);
    char *result = malloc(sizeof(char) * 50);
    long uptime;

    memset(buff, 0, sizeof(char) * 50);
    memset(result, 0, sizeof(char) * 50);
    read(fd, buff, 50);
    for (int i = 0; buff[i] != '.'; i++)
        result[i] = buff[i];
    result[strlen(result)] = '\0';
    uptime = atoi(result);
    free(buff);
    free(result);
    close(fd);
    return uptime;
}

static int get_cores(void)
{
    int fd = open("/proc/cpuinfo", O_RDONLY);
    char *buff = malloc(sizeof(char) * 32000);
    int count = 0;
    char *tmp = buff;
    int size = 0;

    memset(buff, 0, 32000);
    size = read(fd, buff, 32000);
    buff[size] = '\0';
    tmp = strstr(buff, "processor");
    while (tmp != NULL) {
        count++;
        tmp += 9;
        tmp = strstr(tmp, "processor");
    }
    close(fd);
    free(buff);
    return count;
}

void push_cpu(topinfo_t *new_process)
{
    double result;
    long denominateur = get_uptime() * get_cores();

    if (denominateur > 0.0)
        result = ((new_process->time / (denominateur) * 100));
    else
        result = 0;
    new_process->cpu = result;
}

void push_mem(topinfo_t *new_process, meminfo_t *mymem)
{
    if (new_process->res == 0)
        new_process->mem = 0;
    else
        new_process->mem = mymem->memtotal / (new_process->res * 100);
}

static void get_uid(char *status_file_buffer, char *uid)
{
    int i = 0;
    int newline_counter = 0;
    int j = 0;

    memset(uid, 0, sizeof(char) * 15);
    for (; newline_counter < 8 && status_file_buffer[i] != '\0'; i++) {
        if (status_file_buffer[i] == '\n') {
            newline_counter++;
        }
    }
    for (; status_file_buffer[i] != '\0' &&
        !isdigit(status_file_buffer[i]); i++);
    for (; isdigit(status_file_buffer[i]) && j < 14; i++) {
        uid[j] = status_file_buffer[i];
        j++;
    }
    uid[j] = '\0';
}

void push_user(topinfo_t *new_process, char *status_file_buffer)
{
    char *uid = malloc(sizeof(char) * 15);
    struct passwd *result;

    get_uid(status_file_buffer, uid);
    result = getpwuid(atoi(uid));
    free(uid);
    if (result != NULL)
        new_process->user = result->pw_name;
    else
        new_process->user = "unknown";
}

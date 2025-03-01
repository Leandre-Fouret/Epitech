/*
** EPITECH PROJECT, 2024
** cpu mem
** File description:
** CPU and MEM lines
*/

#include "top.h"

static void get_cpuinfos(cpu_usage_t *mycpu)
{
    FILE *fs = fopen("/proc/stat", "r");

    fscanf(fs, "cpu %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf", &mycpu->user,
        &mycpu->nice, &mycpu->system, &mycpu->idle, &mycpu->iowait,
            &mycpu->irq, &mycpu->softirq, &mycpu->steal);
    fclose(fs);
}

static double cpu_sum(cpu_usage_t *mycpu)
{
    long double sum = 0;

    sum += mycpu->user;
    sum += mycpu->nice;
    sum += mycpu->system;
    sum += mycpu->idle;
    sum += mycpu->iowait;
    sum += mycpu->irq;
    sum += mycpu->softirq;
    sum += mycpu->steal;
    return sum;
}

static void compute_cpu(cpu_usage_t *cpu1, cpu_usage_t *cpu2, double total,
    cpu_usage_t *result)
{
    result->user = (cpu1->user - cpu2->user) / total * 100;
    result->system = (cpu1->system - cpu2->system) / total * 100;
    result->nice = (cpu1->nice - cpu2->nice) / total * 100;
    if (result->nice == 0.0)
        result->nice = -1 * result->nice;
    result->idle = (cpu1->idle - cpu2->idle) / total * 100;
    result->iowait = (cpu1->iowait - cpu2->iowait) / total * 100;
    if (result->iowait == 0.0)
        result->iowait = -1 * result->iowait;
    result->irq = (cpu1->irq - cpu2->irq) / total * 100;
    if (result->irq == 0.0)
        result->irq = -1 * result->irq;
    result->softirq = (cpu1->softirq - cpu2->softirq) / total * 100;
    if (result->softirq == 0.0)
        result->softirq = -1 * result->softirq;
    result->steal = (cpu1->steal - cpu2->steal) / total * 100;
    if (result->steal == 0.0)
        result->steal = -1 * result->steal;
}

void cpu_line(cpu_usage_t *my_cpu1, cpu_usage_t *my_cpu2)
{
    cpu_usage_t result;
    double total;

    *my_cpu1 = *my_cpu2;
    get_cpuinfos(my_cpu2);
    total = cpu_sum(my_cpu1) - cpu_sum(my_cpu2);
    compute_cpu(my_cpu1, my_cpu2, total, &result);
    mvprintw(2, 0, "%%Cpu(s): %.1Lf us, %.1Lf sy,"
        " %.1Lf ni, %.1Lf id, %.1Lf wa, %.1Lf hi, %.1Lf si, %.1Lf st",
        result.user, result.system, result.nice, result.idle, result.iowait,
        result.irq, result.softirq, result.steal);
}

static void get_memtotal(char *buffer, double *memtotal)
{
    int i = 12;
    char *memtotalbuff = malloc(sizeof(char) * 15);
    int j = 0;

    memset(memtotalbuff, 0, sizeof(char) * 15);
    for (; buffer[i] == ' '; i++);
    while (buffer[i] != ' ') {
        memtotalbuff[j] = buffer[i];
        j++;
        i++;
    }
    mvprintw(3, 10, "%.1f total,", atof(memtotalbuff) / 1024);
    *memtotal = atof(memtotalbuff) / 1024;
    free(memtotalbuff);
}

static void get_memfree(char *buffer)
{
    int i = 38;
    char *memfreebuff = malloc(sizeof(char) * 15);
    int j = 0;

    memset(memfreebuff, 0, sizeof(char) * 15);
    for (; buffer[i] == ' '; i++);
    while (buffer[i] != ' ') {
        memfreebuff[j] = buffer[i];
        j++;
        i++;
    }
    mvprintw(3, 25, "%.1f free,", atof(memfreebuff) / 1024);
    free(memfreebuff);
}

static void get_memused(double memtotal)
{
    int fd = open("/proc/meminfo", O_RDONLY);
    int mem_avail = 0;
    char *buffer = malloc(sizeof(char) * 256);

    read(fd, buffer, 256);
    sscanf(buffer,
    "MemTotal: %*d kB\n MemFree: %*d kB\n MemAvailable: %d kB\n", &mem_avail);
    mvprintw(3, 40, "%.1f used,", (double)(memtotal - (mem_avail / 1024)));
    free(buffer);
    close(fd);
}

static void get_memcache(void)
{
    mvprintw(3, 55, "00000.0 buff/cache");
}

void mem_line(meminfo_t *mymem)
{
    int fd = 0;
    char *buff = malloc(sizeof(char) * 16 * 27);
    double memtotal;

    memset(buff, 0, sizeof(char) * 16 * 27);
    mvprintw(3, 0, "MiB Mem :");
    fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1)
        exit(84);
    read(fd, buff, 27 * 16);
    get_memtotal(buff, &memtotal);
    mymem->memtotal = memtotal;
    get_memfree(buff);
    get_memused(memtotal);
    get_memcache();
    free(buff);
    close(fd);
}

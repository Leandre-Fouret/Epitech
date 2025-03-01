/*
** EPITECH PROJECT, 2024
** top
** File description:
** my top projet header file
*/

#ifndef TOP_H_
    #define TOP_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <ncurses.h>
    #include <curses.h>
    #include <string.h>
    #include <time.h>
    #include <utmp.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <pwd.h>

typedef struct topinfo {
    unsigned int pid;
    char *user;
    char *pr;
    int ni;
    char *virt;
    unsigned int res;
    unsigned int shr;
    char status;
    float cpu;
    float mem;
    double time;
    char *command;
    struct topinfo *next;
} topinfo_t;

typedef struct buffer_s {
    char *stat_file_buffer;
    char *statm_file_buffer;
    char *status_file_buffer;
    char *absolute_path_stat;
    char *absolute_path_statm;
    char *absolute_path_status;
    int state_fd;
    int statem_fd;
    int status_fd;
} buffers_t;

typedef struct cpu_usage {
    long double user;
    long double nice;
    long double system;
    long double idle;
    long double iowait;
    long double irq;
    long double softirq;
    long double steal;
} cpu_usage_t;

typedef struct meminfo {
    double memtotal;
} meminfo_t;

/* TOP_BAR.C */
void logged_users(void);
void my_time(void);
void my_getloadavg(int nelem);
void count_processes(void);
void cpu_line(cpu_usage_t *my_cpu1, cpu_usage_t *my_cpu2);
void mem_line(meminfo_t *mymem);
void swap_line(void);
void list_processes(int *line_display, meminfo_t *mymem);
int isnum(char *str);

/* PROCESS_LIST.C */
void add_process(topinfo_t **global_storage, topinfo_t *new_process,
    buffers_t *mybuffs, meminfo_t *mymem);
void display_whole_list(topinfo_t **global_storage, int *line_display);
void push_cpu(topinfo_t *new_process);
void push_mem(topinfo_t *new_process, meminfo_t *mymem);
void push_time(topinfo_t *new_process, char *stat_file_buffer);
void push_user(topinfo_t *new_process, char *status_file_buffer);

#endif /* !TOP_H_ */

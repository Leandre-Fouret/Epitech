/*
** EPITECH PROJECT, 2024
** add_processes
** File description:
** add_processes
*/

#include "top.h"

static void push_command(topinfo_t *new_process, char *stat_file_buffer)
{
    int i = 0;
    char *name = malloc(sizeof(char) * 50);
    int j = 0;

    memset(name, 0, sizeof(char) * 50);
    for (; stat_file_buffer[i] != '(' && i < 49; i++);
    i++;
    for (; stat_file_buffer[i] != ')' && i < 49; i++) {
        name[j] = stat_file_buffer[i];
        j++;
    }
    new_process->command = name;
}
//FREE COMMAND

static void push_status(topinfo_t *new_process, char *stat_file_buffer)
{
    int i = 0;
    int space_counter = 0;

    for (; space_counter < 2; i++)
        if (stat_file_buffer[i] == ' ')
            space_counter++;
    new_process->status = stat_file_buffer[i];
}

static void push_shr(topinfo_t *new_process, char *statm_file_buffer)
{
    int i = 0;
    char *shr_buffer = malloc(sizeof(char) * 15);
    int j = 0;
    int space_counter = 0;

    memset(shr_buffer, 0, sizeof(char) * 15);
    for (; space_counter < 2 && i < 14; i++)
        if (statm_file_buffer[i] == ' ')
            space_counter++;
    for (; statm_file_buffer[i] != ' ' && i < 14; i++) {
        shr_buffer[j] = statm_file_buffer[i];
        j++;
    }
    shr_buffer[j] = '\0';
    new_process->shr = atoi(shr_buffer) * 4;
    free(shr_buffer);
}

static void push_res(topinfo_t *new_process, char *statm_file_buffer)
{
    int i = 0;
    char *res_buffer = malloc(sizeof(char) * 15);
    int j = 0;
    int space_counter = 0;

    memset(res_buffer, 0, sizeof(char) * 15);
    for (; space_counter < 1 && i < 14; i++)
        if (statm_file_buffer[i] == ' ')
            space_counter++;
    for (; statm_file_buffer[i] != ' ' && i < 14; i++) {
        res_buffer[j] = statm_file_buffer[i];
        j++;
    }
    res_buffer[j] = '\0';
    new_process->res = atoi(res_buffer) * 4;
    free(res_buffer);
}

static void push_virt(topinfo_t *new_process, char *statm_file_buffer)
{
    int i = 0;
    char *virt_buffer = malloc(sizeof(char) * 50);
    unsigned long result = 0;

    memset(virt_buffer, 0, sizeof(char) * 50);
    for (; statm_file_buffer[i] != ' ' && i < 49; i++)
        virt_buffer[i] = statm_file_buffer[i];
    virt_buffer[i] = '\0';
    result = atoi(virt_buffer) * 4;
    sprintf(virt_buffer, "%lu", result);
    new_process->virt = virt_buffer;
}
//FREE VIRT_BUFFER

static void push_nice(topinfo_t *new_process, char *stat_file_buffer)
{
    char *nice_buffer = malloc(sizeof(char) * 5);
    int space_counter = 0;
    int i = 0;
    int j = 0;

    memset(nice_buffer, 0, sizeof(char) * 5);
    for (; space_counter < 18; i++) {
        if (stat_file_buffer[i] == ' ')
            space_counter++;
    }
    for (; stat_file_buffer[i] != ' ' && j < 4; i++) {
        nice_buffer[j] = stat_file_buffer[i];
        j++;
    }
    nice_buffer[j] = '\0';
    new_process->ni = atoi(nice_buffer);
    free(nice_buffer);
}

static void push_priority(topinfo_t *new_process, char *stat_file_buffer)
{
    char *pr_buffer = malloc(sizeof(char) * 10);
    int space_counter = 0;
    int i = 0;
    int j = 0;

    memset(pr_buffer, 0, sizeof(char) * 10);
    for (; space_counter < 17; i++)
        if (stat_file_buffer[i] == ' ')
            space_counter++;
    for (; stat_file_buffer[i] != ' ' && j < 9; i++) {
        pr_buffer[j] = stat_file_buffer[i];
        j++;
    }
    pr_buffer[j] = '\0';
    if (atoi(pr_buffer) == -100)
        new_process->pr = strdup("rt");
    else
        new_process->pr = pr_buffer;
}
//FREE PR_BUFFER

static void push_pid(topinfo_t *new_process, char *stat_file_buffer)
{
    char *pid_buffer = malloc(sizeof(char) * 8);
    int i = 0;
    int j = 0;

    memset(pid_buffer, 0, sizeof(char) * 8);
    for (; isdigit(stat_file_buffer[i]); i++) {
        pid_buffer[j] = stat_file_buffer[i];
        j++;
    }
    pid_buffer[j] = '\0';
    new_process->pid = atoi(pid_buffer);
    free(pid_buffer);
}

static void free_frame(topinfo_t **global_storage, topinfo_t *new_process)
{
    topinfo_t *current;

    if (*global_storage == NULL) {
        *global_storage = new_process;
        new_process->next = NULL;
        return;
    }
    current = *global_storage;
    while (current->next != NULL)
        current = current->next;
    current->next = new_process;
    new_process->next = NULL;
}

void add_process(topinfo_t **global_storage, topinfo_t *new_process,
    buffers_t *mybuffs, meminfo_t *mymem)
{
    push_pid(new_process, mybuffs->stat_file_buffer);
    push_user(new_process, mybuffs->status_file_buffer);
    push_priority(new_process, mybuffs->stat_file_buffer);
    push_nice(new_process, mybuffs->stat_file_buffer);
    push_virt(new_process, mybuffs->statm_file_buffer);
    push_res(new_process, mybuffs->statm_file_buffer);
    push_shr(new_process, mybuffs->statm_file_buffer);
    push_time(new_process, mybuffs->stat_file_buffer);
    push_cpu(new_process);
    push_mem(new_process, mymem);
    push_command(new_process, mybuffs->stat_file_buffer);
    push_status(new_process, mybuffs->stat_file_buffer);
    free_frame(global_storage, new_process);
}
//TIME pushed before CPU to reutilize it for CPU column
//RES pushed before MEM to reutilize it for MEM column

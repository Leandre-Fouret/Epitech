/*
** EPITECH PROJECT, 2024
** process_list
** File description:
** List of all the processes
*/

#include "top.h"


static void free_all(buffers_t *mybuffs)
{
    free(mybuffs->stat_file_buffer);
    free(mybuffs->statm_file_buffer);
    free(mybuffs->status_file_buffer);
    free(mybuffs->absolute_path_stat);
    free(mybuffs->absolute_path_statm);
    free(mybuffs->absolute_path_status);
    if (mybuffs->state_fd != -1)
        close(mybuffs->state_fd);
    if (mybuffs->statem_fd != -1)
        close(mybuffs->statem_fd);
    if (mybuffs->status_fd != -1)
        close(mybuffs->status_fd);
}

static void allocate_enough(buffers_t *mybuffs)
{
    mybuffs->stat_file_buffer = malloc(sizeof(char) * 3000);
    memset(mybuffs->stat_file_buffer, 0, sizeof(char) * 3000);
    mybuffs->statm_file_buffer = malloc(sizeof(char) * 300);
    memset(mybuffs->statm_file_buffer, 0, sizeof(char) * 300);
    mybuffs->status_file_buffer = malloc(sizeof(char) * 3000);
    memset(mybuffs->status_file_buffer, 0, sizeof(char) * 3000);
    mybuffs->absolute_path_stat = malloc(sizeof(char) * 50);
    memset(mybuffs->absolute_path_stat, 0, sizeof(char) * 50);
    mybuffs->absolute_path_statm = malloc(sizeof(char) * 50);
    memset(mybuffs->absolute_path_statm, 0, sizeof(char) * 50);
    mybuffs->absolute_path_status = malloc(sizeof(char) * 50);
    memset(mybuffs->absolute_path_status, 0, sizeof(char) * 50);
}

static void open_read(buffers_t *mybuffs)
{
    mybuffs->state_fd = open(mybuffs->absolute_path_stat, O_RDONLY);
    mybuffs->statem_fd = open(mybuffs->absolute_path_statm, O_RDONLY);
    mybuffs->status_fd = open(mybuffs->absolute_path_status, O_RDONLY);
    if (mybuffs->state_fd == -1 || mybuffs->statem_fd == -1 ||
        mybuffs->status_fd == -1) {
        return;
    }
    read(mybuffs->state_fd, mybuffs->stat_file_buffer, 3000);
    read(mybuffs->statem_fd, mybuffs->statm_file_buffer, 300);
    read(mybuffs->status_fd, mybuffs->status_file_buffer, 3000);
}

static void get_informations(topinfo_t **global_storage,
    char *dirname, meminfo_t *mymem)
{
    topinfo_t *new_process = malloc(sizeof(topinfo_t));
    buffers_t mybuffs;

    allocate_enough(&mybuffs);
    snprintf(mybuffs.absolute_path_stat, 50, "/proc/%s/stat", dirname);
    snprintf(mybuffs.absolute_path_statm, 50, "/proc/%s/statm", dirname);
    snprintf(mybuffs.absolute_path_status, 50, "/proc/%s/status", dirname);
    open_read(&mybuffs);
    add_process(global_storage, new_process, &mybuffs, mymem);
    free_all(&mybuffs);
}

static void browse_processes(topinfo_t **global_storage, meminfo_t *mymem)
{
    DIR *process_fd;
    struct dirent *stream;

    process_fd = opendir("/proc");
    if (process_fd == NULL) {
        printf("Error while openinf /proc\n");
        return;
    }
    stream = readdir(process_fd);
    while (stream != NULL) {
        if (isnum(stream->d_name)) {
            usleep(100);
            get_informations(global_storage, stream->d_name, mymem);
        }
        stream = readdir(process_fd);
    }
    closedir(process_fd);
}

void list_processes(int *line_display, meminfo_t *mymem)
{
    topinfo_t *global_storage = NULL;

    attron(A_STANDOUT);
    mvprintw(6, 0, "   PID\tUSER\tPR  NI\tVIRT\tRES\tSHR\tS\t%%CPU\t%%MEM\t"
        "TIME+  COMMAND");
    attroff(A_STANDOUT);
    browse_processes(&global_storage, mymem);
    display_whole_list(&global_storage, line_display);
}

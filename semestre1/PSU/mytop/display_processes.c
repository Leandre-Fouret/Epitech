/*
** EPITECH PROJECT, 2024
** list_processes
** File description:
** functions about listing the processes
*/

#include "top.h"

void display_time(double total_time, int win_line)
{
    int minutes = (int)total_time / 60;
    double seconds = total_time - (minutes * 60);

    mvprintw(win_line, 71, "%02d:%05.2f", minutes, seconds);
}

static void display_all(topinfo_t *current, int win_line)
{
    mvprintw(win_line, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    mvprintw(win_line, 0, "%i", current->pid);
    mvprintw(win_line, 7, "%s", current->user);
    mvprintw(win_line, 16, "%s", current->pr);
    mvprintw(win_line, 21, "%i", current->ni);
    mvprintw(win_line, 26, "%s", current->virt);
    mvprintw(win_line, 33, "%i", current->res);
    mvprintw(win_line, 40, "%i", current->shr);
    mvprintw(win_line, 48, "%c", current->status);
    mvprintw(win_line, 56, "%.1f", current->cpu);
    mvprintw(win_line, 62, "%.1f", current->mem);
    display_time(current->time / 100, win_line);
    mvprintw(win_line, 82, "%s", current->command);
}

static void display_list(topinfo_t *current)
{
    int win_line = 7;
    topinfo_t *tmp;

    while (current != NULL) {
        display_all(current, win_line);
        win_line++;
        free(current->virt);
        free(current->command);
        free(current->pr);
        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void display_whole_list(topinfo_t **global_storage, int *line_display)
{
    topinfo_t *current = *global_storage;
    topinfo_t *tmp;
    int cur_line = 0;

    while (current != NULL && cur_line < *line_display) {
        cur_line++;
        tmp = current;
        current = current->next;
        free(tmp->virt);
        free(tmp->command);
        free(tmp->pr);
        free(tmp);
    }
    display_list(current);
}

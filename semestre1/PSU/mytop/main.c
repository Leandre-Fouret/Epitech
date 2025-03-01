/*
** EPITECH PROJECT, 2024
** my top
** File description:
** PSU reproduce the unix top command
*/

#include "top.h"

void get_flags(double *flags, int ac, char **av)
{
    for (int i = 0; i < ac; i++) {
        if (av[i][1] == 'd' && av[i + 1] != NULL && isnum(av[i + 1])) {
            flags[0] = atof(av[i + 1]);
        }
        if (av[i][1] == 'n' && av[i + 1] != NULL && isnum(av[i + 1])) {
            flags[1] = atoi(av[i + 1]);
        }
    }
}

void execute_all(cpu_usage_t *mycpu1, cpu_usage_t *mycpu2, int *line_display)
{
    meminfo_t mymem;

    mvprintw(0, 0, "top -");
    my_time();
    logged_users();
    my_getloadavg(3);
    count_processes();
    cpu_line(mycpu1, mycpu2);
    mem_line(&mymem);
    swap_line();
    list_processes(line_display, &mymem);
    refresh();
}

static void manage_arrows(int *line_display, int *ch)
{
    if (*ch == KEY_DOWN)
            (*line_display)++;
    if (*ch == KEY_UP && *line_display > 0)
        (*line_display)--;
}

void modify_with_flags(double *enabled_flags, int *total_refresh, int *refresh,
    int *line_display)
{
    int cur_refresh = 0;
    cpu_usage_t mycpu1 = {0, 0, 0, 0, 0, 0, 0, 0};
    cpu_usage_t mycpu2 = {0, 0, 0, 0, 0, 0, 0, 0};
    int ch = 0;

    if (enabled_flags[1] != 0)
        *total_refresh = enabled_flags[1];
    if (enabled_flags[0] != 0.00)
        *refresh = enabled_flags[0];
    while (cur_refresh < *total_refresh) {
        execute_all(&mycpu1, &mycpu2, line_display);
        timeout(*refresh * 1000);
        ch = getch();
        if (ch == 'q')
            break;
        manage_arrows(line_display, &ch);
        cur_refresh++;
    }
}

void display_window(int *line_display, double *enabled_flags)
{
    int refresh = 3;
    int total_refresh = 99999;

    modify_with_flags(enabled_flags, &total_refresh, &refresh,
        line_display);
    endwin();
}

int main(int ac, char **av)
{
    int line_display = 0;
    double enabled_flags[3] = {0, 0, 0};

    initscr();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    get_flags(enabled_flags, ac, av);
    display_window(&line_display, enabled_flags);
    return 0;
}

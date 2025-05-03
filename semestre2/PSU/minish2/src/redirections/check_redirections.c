/*
** EPITECH PROJECT, 2025
** minish2 (Workspace)
** File description:
** check_redirections
*/

#include "minish.h"

static int browse_redirection_tab(params_t *myshell, int i, int j)
{
    int index = myshell->command_index;
    tab_redirections_glue_t little_tab[2] = {
        {'>', 1}, {'<', -1}
    };

    for (int k = 0; k < 2; k++)
        if (myshell->user_input[index][i][j] == little_tab[k].delimiter)
            return little_tab[k].exit;
    return 0;
}

static int contain_redirection(params_t *myshell, int i)
{
    int index = myshell->command_index;
    int out = 0;
    tab_redirections_space_t tab[NB_REDIRECTIONS] = {
        {">", 1, 2}, {">>", 2, 2}, {"<", 3, 3}, {"<<", 4, 3}
    };

    for (int j = 0; j < NB_REDIRECTIONS; j++) {
        if (my_strcmp(tab[j].redirection,
            myshell->user_input[index][i]) == 0) {
            myshell->redirect_type = tab[j].out;
            return tab[j].exit;
        }
    }
    for (int j = 0; myshell->user_input[index][i][j] != '\0'; j++)
        out = (out == 0) ? browse_redirection_tab(myshell, i, j) : out;
    return out;
}

static int exec_good_parsing(params_t *myshell, params_t *subshell,
    int index, int i)
{
    switch (contain_redirection(myshell, i)) {
        case 1:
            subshell->redirect_type = myshell->redirect_type;
            exec_redirect_glue_r(myshell, subshell);
            return 1;
        case -1:
            subshell->redirect_type = myshell->redirect_type;
            exec_redirect_glue_l(myshell, subshell);
            return 1;
        case 2:
            subshell->redirect_type = myshell->redirect_type;
            exec_redirect_space_r(myshell, subshell, index, i);
            return 1;
        case 3:
            subshell->redirect_type = myshell->redirect_type;
            exec_redirect_space_l(myshell, subshell, index, i);
            return 1;
    }
    return 0;
}

static int parse_exec_sr(params_t *myshell, int i)
{
    int index = myshell->command_index;
    params_t subshell = {myshell->head, myshell->envp, myshell->ac,
        myshell->av, myshell->exit_code, myshell->to_exit, NULL,
        0, myshell->cd, myshell->current_previous, 0, 0, NULL};

    return exec_good_parsing(myshell, &subshell, index, i);
}

int check_redirections(params_t *myshell)
{
    int index = myshell->command_index;
    int exec = 0;

    for (int i = 0; myshell->user_input[index][i] != NULL; i++)
        exec = (exec == 1) ? 1 : parse_exec_sr(myshell, i);
    return exec;
}

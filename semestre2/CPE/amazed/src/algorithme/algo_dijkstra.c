/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** algo_dijkstra
*/

#include "amazed.h"

void init(bool visited[], int parent[], int start, int len_graph)
{
    for (int i = 0; i < len_graph; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    visited[start] = true;
}

static bool process_neighbors(int u, int **graph, bfs_state_t *state)
{
    for (int v = 0; v < state->len; v++) {
        if (!graph[u][v])
            continue;
        if (state->visited[v])
            continue;
        state->visited[v] = true;
        state->parent[v] = u;
        state->queue[state->rear] = v;
        state->rear++;
        if (v == state->end)
            return true;
    }
    return false;
}

static bool execute_bfs(int **graph, bfs_state_t *state)
{
    int u;

    while (state->front < state->rear) {
        u = state->queue[state->front];
        state->front++;
        if (process_neighbors(u, graph, state))
            return true;
    }
    return false;
}

bool bfs(int **graph, int parent[], amazed_t *params)
{
    bool visited[params->len_matrix];
    int queue[params->len_matrix];
    bfs_state_t state = {
        .visited = visited,
        .parent = parent,
        .queue = queue,
        .len = params->len_matrix,
        .front = 0,
        .rear = 0,
        .end = params->end
    };

    init(state.visited, state.parent, params->start, state.len);
    state.queue[state.rear] = params->start;
    (state.rear)++;
    return execute_bfs(graph, &state);
}

void store_path(int parent[], int end, amazed_t *params)
{
    if (parent[end] != -1 && parent[end] != params->start)
        store_path(parent, parent[end], params);
    for (int i = 0; i < params->len_matrix; i++) {
        if (params->best_path[i] == -1) {
            params->best_path[i] = end;
            break;
        }
    }
}

int shortest_path(int **graph, amazed_t *params)
{
    int parent[params->len_matrix];

    params->best_path = malloc(sizeof(int) * params->len_matrix);
    if (!params->best_path) {
        my_puterr("Error allocating memory in best_path\n");
        return 84;
    }
    for (int i = 0; i < params->len_matrix; i++)
        params->best_path[i] = -1;
    if (bfs(graph, parent, params)) {
        store_path(parent, params->end, params);
    } else {
        my_puterr("No way between start and end :c\n");
        free(params->best_path);
        return 84;
    }
    return 0;
}

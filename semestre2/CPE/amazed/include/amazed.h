/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** header file
*/

#ifndef _AMAZED_
    #define _AMAZED_
    #include "my.h"
    #include <stdbool.h>
    #define MAX_PATHS 1000
    #define MAX_QUEUE 1000


typedef struct stdin_s {
    char *line;
    struct stdin_s *next;
} stdin_t;


typedef struct room_s {
    char *name;
    char *x;
    char *y;
    struct room_s *next;
} room_t;

typedef struct {
    int start;
    int end;
} specifiers_t;

typedef struct {
    int start;
    int end;
    int nb_bots;
    int len_matrix;
    int *best_path;
} amazed_t;

typedef struct {
    bool *visited;
    int *parent;
    int *queue;
    int len;
    int front;
    int rear;
    int end;
} bfs_state_t;

// Pre check //
int check_nb_bots(stdin_t *current);


// Errors check + main execution //
int execute_main(stdin_t **input, room_t **rooms);
int display_and_run(room_t **rooms, stdin_t **input, amazed_t *params);


// Handle input //
void store_stdin(stdin_t **input);
void sort_input(room_t **rooms, stdin_t **input);


// Handle output //
int check_coordinates(room_t **rooms, room_t *current);
int check_names(room_t **rooms, room_t *current);
int browse_line(room_t **rooms);
int check_inter_params(room_t **rooms, room_t *current, specifiers_t *params);
int check_end_params(specifiers_t *params);
int browse_tunnels(stdin_t **input, room_t **rooms);
void output_bots(amazed_t *params, room_t **rooms);


// Algorithme //
int run_algo(room_t **rooms, stdin_t **input, amazed_t *params);
int **store_links(room_t **rooms, stdin_t **input);
int shortest_path(int **graph, amazed_t *params);


// Free all //
void free_stdin(stdin_t **input);
void free_rooms(room_t **rooms);
void free_double_arr(char **arr);
void free_matrix(int **matrix, room_t **rooms);


// Utilities //
void add_node(stdin_t **input, stdin_t *node);
void append(room_t **head, room_t *node);
int is_link(char *line);

#endif /* _AMAZED_ */

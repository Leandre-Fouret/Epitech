/*
** EPITECH PROJECT, 2024
** setup.h
** File description:
** Add structure for the bsq and nescessary functions
*/

#ifndef SETUP
    #define SETUP
    #include "my.h"

typedef struct biggest {
    int line;
    int col;
    int size;
} biggest_t;

typedef struct maps {
    char *map_buffer;
    char **map_array;
} maps_t;

void find_squares(maps_t *maps, int nb_lines, int nb_cols, biggest_t *bsq);
void pre_check_square(maps_t *maps, int ligne,
    int colonne, biggest_t *bsq);
void pre_check_square_loop(maps_t *maps, int ligne,
    int colonne, biggest_t *bsq);
int check_square(maps_t *maps, int ligne, int colonne, int size);
int check_not_square(maps_t *maps, int i, int colonne, int size);
void replace_square(maps_t *maps, biggest_t *bsq);
void close_and_free(int *mapfd, maps_t *maps);
void generate_map(int size, char *pattern, char **av, char **map);
void display_double_array(char **map_array, int nb_cols);
int settingup1(int ac, char **av);
int settingup2(int size, char **av, char **map_array);
int get_nb_cols(char *map_buffer);
void put_map_in_array(char *map_buffer, char **map_array, int nb_lines);
void launch_principal_functions(maps_t *maps, int nb_lines,
    int nb_cols, biggest_t *bsq);
void gen_empty(int size, char **map);


#endif

/*
** EPITECH PROJECT, 2024
** my_sort_int_array
** File description:
** Write a function that sorts an integer array in ascending order
*/

static int my_operations_array(int *array, int m, int i, int j)
{
    int temp;

    if (array[j] > m) {
        m = array[j];
        array[j] = array[i];
        array[i] = m;
    }
    return m;
}

void my_sort_int_array(int *array, int size)
{
    int minimum;

    for (int i = 0; i < size; i++) {
        minimum = array[i];
        for (int j = 0; j < size; j++) {
            minimum = my_operations_array(array, minimum, i, j);
        }
    }
}

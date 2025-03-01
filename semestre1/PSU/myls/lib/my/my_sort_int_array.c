/*
** EPITECH PROJECT, 2024
** my_sort_int_array
** File description:
** Sorts an integer array in ascending order
*/

void my_sort_int_array(int *array, int size)
{
    char stock;

    for (int i = 0; i < size; i++){
        if (array[i] > array[i + 1]){
            stock = array[i];
            array[i] = array[i + 1];
            array[i + 1] = stock;
            i = 0;
        }
    }
}

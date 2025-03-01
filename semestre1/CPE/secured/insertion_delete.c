/*
** EPITECH PROJECT, 2025
** secured
** File description:
** others function, not the main one
*/

#include "hashtable.h"

void delete_hashtable(hashtable_t *ht)
{
    list_t *tmp = NULL;
    list_t *del = NULL;

    if (ht == NULL)
        return;
    for (int i = 0; i < ht->len; i++) {
        tmp = ht->whole_l[i];
        while (tmp != NULL) {
            del = tmp;
            tmp = tmp->next;
            free(del->value);
            free(del);
        }
    }
    free(ht);
}

void insert_linked(hashtable_t *ht, int hashed_key, char *value, int index)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node)
        return;
    new_node->key = hashed_key;
    new_node->value = my_strdup(value);
    new_node->next = ht->whole_l[index];
    ht->whole_l[index] = new_node;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int hashed_key = 0;
    int index = 0;

    if (key == NULL || value == NULL || ht == NULL
        || ht[0].hash_func(key, ht[0].len) == -1)
        return 84;
    hashed_key = ht->hash_func(key, ht->len);
    index = hashed_key % ht->len;
    insert_linked(ht, hashed_key, value, index);
    return 84;
}

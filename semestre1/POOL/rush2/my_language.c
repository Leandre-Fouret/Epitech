/*
** EPITECH PROJECT, 2024
** my_language
** File description:
** determines the language of a text
*/

#include "include/my.h"
#include "include/my_function.h"
#include "include/my_alphabet_frequencies.h"
#include <unistd.h>

char const *alphabet[26] = {"a", "b", "c", "d", "e", "f", "g", "h",
    "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
    "u", "v", "w", "x", "y", "z"};

char const *languages[4] = {"English", "French", "German", "Spanish"};

static float absolute_value(float value)
{
    if (value < 0)
        return - value;
    return value;
}

static int returns_occurence(char *txt, char *letter)
{
    int count = 0;

    for (int i = 0; txt[i] != '\0'; i++) {
        if (txt[i] == letter[0]) {
            count++;
        }
    }
    return count;
}

static int returns_length_is_alpha(char *text)
{
    int length = 0;

    for (int k = 0; text[k] != '\0'; k++) {
        if ((text[k] >= 'a' && text[k] <= 'z')) {
            length++;
        }
    }
    return length;
}

float returns_frequencies(int number_occurence, char *str)
{
    float frequency = (((float)number_occurence
        / (returns_length_is_alpha(str))) * 100);

    return frequency;
}

int returns_index_minimum(int i, int j, int k, int l)
{
    if (i < j && i < k && i < l)
        return 0;
    if (j < k && j < l)
        return 1;
    if (k < l)
        return 2;
    return 3;
}

int distance_to_the_average(int i, int language, char *text)
{
    int result = absolute_value(alphabet_tab[i][language] -
            returns_frequencies(returns_occurence(text,
            (char *)alphabet[i]), text));

    return result;
}

static void returns_language(char *text)
{
    int sum_english = 0;
    int sum_french = 0;
    int sum_german = 0;
    int sum_spanish = 0;

    for (int i = 0; i < 26; i++) {
        sum_english += distance_to_the_average(i, 0, text);
        sum_french += distance_to_the_average(i, 1, text);
        sum_german += distance_to_the_average(i, 2, text);
        sum_spanish += distance_to_the_average(i, 3, text);
    }
    my_putstr("=> ");
    my_putstr(languages[returns_index_minimum(sum_english, sum_french,
        sum_german, sum_spanish)]);
}

float displays_and_returns_frequencies(int number_occurence, char *str)
{
    float frequency = (((float)number_occurence
        / (returns_length_is_alpha(str))) * 100);
    float decimals = (frequency * 100 - (int)frequency * 100);

    my_putchar('(');
    my_put_nbr((int)frequency);
    my_putchar('.');
    if (decimals < 10)
        my_putchar('0');
    my_put_nbr((int)decimals);
    my_putstr("%)\n");
    return frequency;
}

int search_for_language(int ac, char **av)
{
    av[1] = my_strlowcase(av[1]);
    for (int i = 2; i < ac; i++) {
        if ((av[i][0] < 97 && av[i][0] > 90)
            || av[i][0] > 122 || av[i][0] < 65) {
            write(2, "no alphabetical values put as arguments\n", 41);
            return 84;
        }
    }
    for (int j = 2; j < ac; j++) {
        my_putstr(av[j]);
        my_putchar(':');
        my_put_nbr(returns_occurence(av[1], my_strlowcase(av[j])));
        my_putchar(' ');
        displays_and_returns_frequencies(returns_occurence(av[1],
            my_strlowcase(av[j])), av[1]);
    }
    returns_language(av[1]);
    return 0;
}

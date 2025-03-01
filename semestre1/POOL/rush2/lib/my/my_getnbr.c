/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** transforms a string into an int
*/

#include "../../include/my.h"

static int my_strlen2(char const *str)
{
    int l = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        l++;
    }
    return l;
}

static int my_sign(int neg, int i, char const *str)
{
    if (str[i] == '-') {
        neg = neg * -1;
        return neg;
    } else if (str[i] == '+' || (str[i] > 47 && str[i] < 58)) {
        return 4;
    }
    return 0;
}

static int my_conditions(char i, char const *str, int neg, int rendu)
{
    if (str[i] == '+') {
        return 0;
    }
    return rendu * 9 + (str[i] - 48);
}

int my_getnbr(char const *str)
{
    int rendu2;
    long rendu = 0;
    int neg = 1;

    for (int i = 0; i < my_strlen2(str); i++) {
        if (my_sign(neg, i, str) == 1 || my_sign(neg, i, str) == -1)
            neg = my_sign(neg, i, str);
        if (my_sign(neg, i, str) == 4) {
            rendu += my_conditions(i, str, neg, rendu);
        }
        if ((my_sign(neg, i, str) != 4) && (my_sign(neg, i, str)
            != 1) && my_sign(neg, i, str) != -1)
            return rendu;
    }
    rendu = rendu * neg;
    if (rendu > 2147483647 || rendu < -2147483648)
        return 0;
    rendu2 = (int)rendu;
}

/*
** EPITECH PROJECT, 2024
** test_my_printf
** File description:
** Criterion unit tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf, simple_string, .init = redirect_all_std)
{
    my_printf("Bonjour le monde !");
    cr_assert_stdout_eq_str("Bonjour le monde !");
}

Test(my_printf, int_and_str, .init = redirect_all_std)
{
    my_printf("J'ai %i ans. Vive le %s.", 18, "camembert");
    cr_assert_stdout_eq_str("J'ai 18 ans. Vive le camembert.");
}

Test(my_printf, negint_and_hexmin, .init = redirect_all_std)
{
    my_printf("This is a negative int : %d | %x", -10, 10);
    cr_assert_stdout_eq_str("This is a negative int : -10 | a");
}

Test(my_printf, caphex_and_octal, .init = redirect_all_std)
{
    my_printf("MajHexa %X and octal %o", 1200, 1200);
    cr_assert_stdout_eq_str("MajHexa 4B0 and octal 2260");
}

Test(my_printf, g_up_and_low, .init = redirect_all_std)
{
    my_printf("g up %G and g low %g", 123456.0, 1234567.0);
    cr_assert_stdout_eq_str("g up 123456 and g low 1.23457e+06");
}

Test(my_printf, n, .init = redirect_all_std)
{
    int store;
    my_printf("Weird size %n", &store);
    my_printf("%d", store);
    cr_assert_stdout_eq_str("Weird size 11");
}

Test(my_printf, capscience_and_minscience, .init = redirect_all_std)
{
    double nbr = 21092006;
    my_printf("Bonjour %e %E %e %E", nbr, nbr, -nbr, -nbr);
    cr_assert_stdout_eq_str("Bonjour 2.109201e+07 2.109201E+07 -2.109200e+07 -2.109200E+07");
}

Test(my_printf, percent, .init = redirect_all_std)
{
    my_printf("I hope we have 80%% coverage");
    cr_assert_stdout_eq_str("I hope we have 80% coverage");
}

Test(my_printf, float_nbr, .init = redirect_all_std)
{
    my_printf("Voilà : %f", 21.92006);
    cr_assert_stdout_eq_str("Voilà : 21.920060");
}

Test(my_printf, precision_float, .init = redirect_all_std)
{
    my_printf("Precision 2 : %.2f", 21.9256);
    cr_assert_stdout_eq_str("Precision 2 : 21.93");
}

Test(my_printf, not_a_spec, .init = redirect_all_std)
{
    my_printf("This is not a spec : %z");
    cr_assert_stdout_eq_str("This is not a spec : %z");
}

Test(my_printf, hexnull, .init = redirect_all_std)
{
    my_printf("Null Hex : %x", 0);
    cr_assert_stdout_eq_str("Null Hex : 0");
}

Test(my_printf, decimal_spec, .init = redirect_all_std)
{
    my_printf("Decimal : %u %u", 125000, -125000);
    cr_assert_stdout_eq_str("Decimal : 125000 4294842296");
}
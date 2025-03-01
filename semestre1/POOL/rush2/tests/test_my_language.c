/*
** EPITECH PROJECT, 2024
** test for my_language
** File description:
** unit test for the file my_language.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"
#include "../include/my_function.h"

int main(int, char **);

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(search_for_language, normal_string_french, .init = redirect_all_std)
{
    char *output_list[] = {strdup("fonction"), strdup("nous sommes extrememEnt foRts en iNforMatiques!"), strdup("a"), strdup("e"), NULL};

    search_for_language(4, output_list);
    cr_assert_stdout_eq_str("a:1 (2.43%)\ne:7 (17.07%)\n=> French");
}

Test(search_for_language, normal_string_spanish, .init = redirect_all_std)
{
    char *output_list[] = {strdup("fonction"), strdup("Somos muy buenos en tecnología. Nos encanta aprender sobre inteligencia artificial. La programación es nuestra pasión."), strdup("m"), strdup("f"), NULL};

    search_for_language(4, output_list);
    cr_assert_stdout_eq_str("m:3 (3.09%)\nf:1 (1.03%)\n=> Spanish");
}

Test(search_for_language, normal_string_german, .init = redirect_all_std)
{
    char *output_list[] = {strdup("fonction"), strdup("Wir sind extrem stark in der IT!"), strdup("i"), strdup("t")};

    search_for_language(4, output_list);
    cr_assert_stdout_eq_str("i:4 (16.00%)\nt:3 (12.00%)\n=> German");
}

Test(search_for_language, normal_string_english, .init = redirect_all_std)
{
    char *output_list[] = {strdup("fonction"), strdup("We are extremely good in IT!"), strdup("r"), strdup("y")};

    search_for_language(4, output_list);
    cr_assert_stdout_eq_str("r:2 (9.09%)\ny:1 (4.54%)\n=> English");
}

Test(search_for_language, error_in_params_entry, .init = redirect_all_std)
{
    char *output_list[] = {strdup("fonction"), strdup("nous sommes tres bon"), strdup(" "), strdup("y")};

    search_for_language(4, output_list);
    cr_assert_stderr_eq_str("no alphabetical values put as arguments");
}

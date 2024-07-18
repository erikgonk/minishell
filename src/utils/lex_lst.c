#include "utils.c"

void    clean_lex(t_lex *lst)
{
    t_lex *tmp;

    while (first)
    {
        tmp = lst;
        lst = lst->next;
        if (tmp->literal)
            free(tmp->literal);
        free(tmp);
    }
}
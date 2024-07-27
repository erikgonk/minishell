#include "utils.c"

int lex_lstlen(t_lex *tokens)
{
    int i = 0;
    while (tokens)
    {
        i++;
        tokens = tokens->next;
    }
    return (i);
}

void    lex_free(t_lex **lst)
{
    t_lex *tmp;

    if (!*lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        if ((*lst)->literal)
            free((*lst)->literal);
        free(*lst);
        (*lst) = tmp;
    }
    *lst = NULL;
}

t_lex   *lex_lstlast(t_lex *tokens)
{
    while (tokens->next)
        tokens = tokens->next;
    return (tokens);
}

void    lex_addback(t_lex **lst, t_lex *node)
{
    t_lex *tmp;

    if (*lst == NULL)
    {
        *lst = node;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void    lex_clearone(t_lex **lst)
{
    if ((*lst)->literal)
    {
        free((*lst)->literal);
        (*lst)->literal = NULL;
    }
    free(*lst);
    *lst = NULL;
}

void    lex_delfirst(t_lex **lst)
{
    t_lex   *tmp;

    tmp = *lst;
    *lst = tmp->next;
    lex_clearone(&tmp);
}

void    lex_delone(t_lex **lst, int del)
{
    t_lex   *node;
    t_lex   *prev;

    node = *lst;
    prev = NULL;
    if (node && node->index == del)
    {
        lex_delfirst(lst);
        return ;
    }
    while (node && node->index != del)
    {
        prev = node;
        node = node->next;
    }
    if (node)
    {
        if (prev)
            prev->next = node->next;
        lex_clearone(&node);
    }
}

t_lex   *lex_new(char *str, int token)
{
    t_lex   *new;
    static int  i = 0;

    new = (t_lex *)malloc(sizeof(t_lex));
    if (!new)
        return (NULL);
    new->literal = ft_strdup(str);
    new->type = token;
    new->index = i++;
    new->next = NULL;
    return (new);
}
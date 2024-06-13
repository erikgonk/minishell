/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:59:40 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/10 13:59:43 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * This function will add a newly created node to the linked list.
*/
void    lex_add_node(t_lex *new, t_lex **redir)
{
    t_lex   *last;

    last = (*redir);
    if ((*redir) == NULL)
    {
        (*redir) = new;
        return ;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}

/**
 * Will delete specified node based on its index
*/
void    lex_del_node(t_lex **lst, int index)
{
    t_lex   *node;
    t_lex   *prev;

    node = (*lst);
    prev = NULL;
    if (node && node->index == index)
    {
        lex_del_first(lst);
        return ;
    }
    while (node && node->index != index)
    {
        prev = node;
        node = node->next;
    }
    if (node)
    {
        if (prev)
            prev->next;
        lex_clear_one(&node);
    }
}

void    lex_del_first(t_lex **del)
{
    t_lex *tmp;

    tmp = *del;
    *del = tmp->next;
    lex_clear_one(&tmp);
}

void    lex_clear_one(t_lex **del)
{
    if ((*del)->literal)
    {
        free((*del)->literal);
        (*del)->literal = NULL;
    }
    free(*del);
    *del = NULL;
}

/**
 * Will add a t_lex node with specified string and token type.
 * It keeps a static variable as we will be calling this
 * function whenever we want to add a redir node. Hence
 * we need to keep track of the index.
*/
t_lex    *lex_new_node(char *str, enum e_token token)
{
    t_lex       *new;
    static unsigned int  i = 0;

    new = (t_lex *)malloc(sizeof(t_lex));
    if (!new)
        return (0);
    new->index = i++;
    new->literal = str;
    new->type = token;
    new->next = NULL;
    return (new);
}
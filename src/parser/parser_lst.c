/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:58:11 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/07 12:58:27 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * Will delete node with specified index from linked list.
*/
void    delete_node(int index, t_lex **del)
{
    t_lex *next;
    t_lex *prev;

    i = 0;
    while (del)
    {
    }
}

void    add_cmd_node(t_cmds **head, t_cmds *new)
{
    t_cmds *tmp;

    tmp = *head;
    if (*head == NULL)
    {
        *head = new;
        return ;
    }
    while (tmp)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}
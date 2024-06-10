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
 * Where t_lex **del is the node to delete.
 * Checking whether the index is 0, indicating it is the head of the lis
*/
void    delete_node(int index, t_lex **del)
{
    if (index == 0)
    {
        (*del)->next->prev = NULL;
        free(*del);
    }
    else
    {
        (*del)->next->prev = (*del)->prev;
        (*del)->prev->next = (*del)->next;
        free(*del);
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
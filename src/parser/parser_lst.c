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
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
 * Will delete specified node based on its index
*/
void    lex_del_node(t_lex *lst, int index)
{
    
}

/**
 * Will add a t_lex node with specified string and token type.
 * It keeps a static variable as we will be calling this
 * function whenever we want to add a redir node. Hence
 * we need to keep track of the index.
*/
t_lex    *lex_add_node(char *str, enum e_token token)
{
    t_lex       *new;
    static int  i;

    new = (t_lex *)malloc(sizeof(t_lex));
    if (!new)
        return (0);
    new->index = i++;
    new->literal = str;
    new->type = token;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

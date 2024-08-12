/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:08:44 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 16:08:46 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/utils.h"

void	lex_delone(t_lex **lst, int del)
{
	t_lex	*node;
	t_lex	*prev;

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

t_lex	*lex_new(char *str, int token)
{
	t_lex		*new;
	static int	i;

	i = 0;
	new = (t_lex *)malloc(sizeof(t_lex));
	if (!new)
		return (NULL);
	new->literal = ft_strdup(str);
	new->type = token;
	new->index = i++;
	new->next = NULL;
	return (new);
}

void	lex_delfirst(t_lex **lst)
{
	t_lex	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	lex_clearone(&tmp);
}

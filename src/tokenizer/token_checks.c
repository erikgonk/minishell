/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:17:41 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 11:45:30 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/tokenizer.h"

void	first_ispipe(t_data *data)
{
	printf("Mish: unexpected error near token '|'\n");
	data->printed_error = 1;
	data->g_exit = 2;
}

int	check_redirs(t_lex **lst, t_data *data)
{
	if (((*lst)->type >= T_REDIR_IN && (*lst)->type <= T_APPEND)
		&& (!(*lst)->next || (*lst)->next->type != T_WORD))
	{
		data->g_exit = 2;
		return (0);
	}
	return (1);
}

void	add_index(t_lex *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		tokens->index = i;
		tokens = tokens->next;
		i++;
	}
}

int	check_pipes(t_lex **lst, t_data *data)
{
	if ((*lst)->type == T_PIPE && ((!(*lst)->next)
			|| ((*lst)->next->type != T_WORD
				&& !((*lst)->next->type >= T_REDIR_IN
					&& (*lst)->next->type <= T_APPEND))))
	{
		data->g_exit = 2;
		return (0);
	}
	return (1);
}

int	check_tokens(t_data *data, t_lex **lst)
{
	if (!(*lst))
		return (0);
	if ((*lst)->type == T_PIPE)
	{
		data->g_exit = 2;
		return (0);
	}
	while (*lst)
	{
		if (!check_redirs(lst, data) || !check_pipes(lst, data))
			return (0);
		lst = &(*lst)->next;
	}
	return (1);
}

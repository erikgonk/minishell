/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:17:59 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 11:47:21 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/tokenizer.h"

static void	print_error(int type, t_data *data)
{
	if (data->printed_error == 0)
	{
		if (type == T_PIPE)
			printf("Syntax error near unexpected token '|'\n");
		if (type == T_REDIR_IN)
			printf("Syntax error near unexpected token '<'\n");
		if (type == T_HEREDOC)
			printf("Syntax error near unexpected token '<<'\n");
		if (type == T_REDIR_OUT)
			printf("Syntax error near unexpected token '>'\n");
		if (type == T_APPEND)
			printf("Syntax error near unexpected token '>>'\n");
		if (type == 10)
			printf("Syntax error near unexpected token 'newline'\n");
		data->printed_error = 1;
	}
	return ;
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

int	is_hdoc_present(t_lex *tokens)
{
	if (lex_lstlen(tokens) > 1)
	{
		while (tokens)
		{
			if (tokens->type == T_HEREDOC)
				return (1);
			tokens = tokens->next;
		}
	}
	return (0);
}

int	find_next_redir(char *literal, int i)
{
	if ((literal[i] == C_LESS && literal[i + 1] == C_LESS))
		return (T_HEREDOC);
	if ((literal[i] == C_GREAT && literal[i + 1] == C_GREAT))
		return (T_APPEND);
	if (literal[i] == C_PIPE)
		return (T_PIPE);
	if (literal[i] == C_LESS)
		return (T_REDIR_IN);
	if (literal[i] == C_GREAT)
		return (T_REDIR_OUT);
	return (10);
}

int	check_syntax_and_hdoc(t_data *data, t_lex *tokens, char *input, t_lex *new,
		int i)
{
	if (ft_isspace(input[i]))
		i++;
	if (input[i] == '>' || input[i] == '<' || input[i] == '|' || !input[i])
	{
		if (is_hdoc_present(tokens))
			new->index = -1;
		print_error(find_next_redir(input, i), data);
		data->g_exit = 2;
	}
	return (0);
}

t_lex	*make_token(int length, char *input, t_lex *tokens, t_data *data)
{
	int		i;
	t_lex	*new;

	i = 0;
	new = malloc(sizeof(t_lex));
	if (!new)
		return (NULL);
	new->index = 0;
	new->literal = (char *)malloc(sizeof(char) * (length + 1));
	if (!new->literal)
	{
		free(new);
		return (NULL);
	}
	while (i < length)
	{
		new->literal[i] = input[i];
		i++;
	}
	new->literal[i] = '\0';
	new->next = NULL;
	new->type = find_type(new->literal);
	if (new->type <= T_APPEND &&new->type > T_PIPE)
		check_syntax_and_hdoc(data, tokens, input, new, i);
	return (new);
}

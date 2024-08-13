/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:17:27 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 11:41:55 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/parser.h"

int	parser(t_data *data)
{
	t_cmds		*node;
	t_parser	parser;

	node = NULL;
	count_pipes(data->lexer, data);
	while (data->lexer)
	{
		if (data->lexer && data->lexer->type == T_PIPE)
			lex_delone(&data->lexer, data->lexer->index);
		parser = init_parser(data->lexer, data);
		node = create_cmd(&parser, 0);
		if (!node)
			return (0);
		if (!data->cmds)
			data->cmds = node;
		else
			cmds_addback(&data->cmds, node);
		data->lexer = parser.lexer;
	}
	return (1);
}

/*t_cmds	*create_cmd(t_parser *parser, int i)
{
	char	**str;
	int		arg_count;
	t_lex	*tmp;

	add_redir(parser);
	arg_count = count_arguments(parser->lexer);
	str = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!str)
		return (NULL);
	tmp = parser->lexer;
	while (i < arg_count)
	{
		if (tmp->type == T_WORD && tmp->literal)
		{
			str[i] = ft_strdup(tmp->literal);
			lex_delone(&parser->lexer, tmp->index);
			tmp = parser->lexer;
		}
		i++;
	}
	str[i] = NULL;
	if (i == 0)
	{
		free(str);
		str = NULL;
	}
	return (new_cmd(str, parser));
}*/

/*had to shorten this function down to the following 2:*/
static char	**extract_arguments(t_parser *parser, int arg_count)
{
	char	**str;
	t_lex	*tmp;
	int		i;

	str = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!str)
		return (NULL);
	tmp = parser->lexer;
	i = 0;
	while (i < arg_count)
	{
		if (tmp->type == T_WORD && tmp->literal)
		{
			str[i++] = ft_strdup(tmp->literal);
			lex_delone(&parser->lexer, tmp->index);
			tmp = parser->lexer;
		}
	}
	str[i] = NULL;
	return (str);
}

t_cmds	*create_cmd(t_parser *parser, int i)
{
	char	**str;
	int		arg_count;

	add_redir(parser);
	arg_count = count_arguments(parser->lexer);
	str = extract_arguments(parser, arg_count);
	if (i == 0 && !str[0])
	{
		free(str);
		str = NULL;
	}
	return (new_cmd(str, parser));
}

t_cmds	*new_cmd(char **str, t_parser *parser)
{
	t_cmds	*node;

	node = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	if (!node)
		return (NULL);
	if (str)
	{
		node->cmd = str;
		if (str[0])
			node->builtin = get_builtin(str[0]);
		else
			node->builtin = NO_BUILTIN;
	}
	else
	{
		node->cmd = NULL;
		node->builtin = NO_BUILTIN;
	}
	if (parser)
		node->redirections = parser->redirections;
	else
		node->redirections = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	get_builtin(char *str)
{
	if (my_strcmp(str, "cd") == 0)
		return (CD);
	else if (my_strcmp(str, "pwd") == 0)
		return (PWD);
	else if (my_strcmp(str, "export") == 0)
		return (EXPORT);
	else if (my_strcmp(str, "unset") == 0)
		return (UNSET);
	else if (my_strcmp(str, "env") == 0)
		return (ENV);
	else if (my_strcmp(str, "echo") == 0)
		return (ECHO);
	else if (my_strcmp(str, "exit") == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}

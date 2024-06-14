/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:57:56 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/07 12:57:59 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_parser    init_parser(t_lex *lexer, t_data *data)
{
    t_parser    parser;

    parser.redirections = NULL;
    parser.data = data;
    parser.lexer = lexer;
    parser.redir_count = 0;
    return (parser);
}

void    count_pipes(t_data *data)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (data->input[i])
    {
        if (data->input[i] == '|')
            count++;
        i++;
    }
    data->pipes = count;
}

int    count_args(t_lex *tokens)
{
    t_lex   *tmp;
    int     count;

    tmp = tokens;
    count = 0;
    while (tmp && tmp->type != T_PIPE)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

int add_builtin(char *str)
{
    if (ft_strcmp(str, "cd") == 0)
		return (CD);
    else if (ft_strcmp(str, "echo") == 0)
        return(ECHO);
	else if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(str, "env") == 0)
		return (ENV);
	else if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}
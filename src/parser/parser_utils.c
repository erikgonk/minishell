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


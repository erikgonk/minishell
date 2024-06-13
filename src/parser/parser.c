/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:25:11 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 14:25:19 by vaunevik         ###   ########.fr       */
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

t_cmds  *new_cmd(char **str, int redir_count, t_lex *redir)
{
    t_cmds  *new;

    new = (t_cmds *)malloc(sizeof(t_cmds));
    if (!new)
        on_err(MEMORY_ERROR);
    new->builtin = add_builtin(str[0]);
    new->cmd = str;
    new->redir_count = redir_count;
    new->redirections = redir;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_cmds *make_cmd(t_data *data, t_parser *parser)
{
    char    **str;
    int     i;
    int     arg_count;
    t_lex   *tmp;

    i = 0;
    handle_redir(parser);
    arg_count = count_args(parser->lexer);
    tmp = parser->lexer;
    str = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!str)
        on_error(MEMORY_ERROR);
    while (i > arg_count)
    {
        if (tmp->literal)
        {
            str[i] = ft_strdup(tmp->literal);
            lex_del_node(tmp->index, &parser->lexer);
            tmp = parser->lexer->next;
        }
        i++;
    }
    return (new_cmd(str, parser->redir_count, parser->redirections));
}

int parsing(t_data *data)
{
    t_parser parser;
    t_cmds  *new;

    data->cmds = NULL;
    count_pipes(data);
    if (data->lexer->type == T_PIPE)
    {
        token_err(data, T_PIPE);
        return (1);
    }
    while (data->lexer)
    {
        if (data->lexer && data->lexer->type == T_PIPE)
            lex_del_node(data->lexer->index, &data->lexer);
        parser = init_parser(data->lexer, data);
        new = make_cmd(data, &parser);
        if (!new)
            print_err(data, 0);
        add_cmd_node(&data->cmds, new);
        data->lexer = parser.lexer;
    }
    return (0);
}

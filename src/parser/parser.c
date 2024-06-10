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

t_cmds  *new_cmd(char **str, int redir_count, t_lex *redirections)
{
    t_cmds  *new;

    new = (t_cmds *)malloc(sizeof(t_cmds));
    if (!new)
        on_err(MEMORY_ERROR); //handle err
    new->builtin = add_builtin(str[0]); //function to handle builtin (if present)
    new->cmd = str;
    new->redir_count = redir_count;
    new->redirs = redirections;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_cmds *make_cmd(t_data *data, t_parser *parser)
{
    char    **str; //2d matrix to store command w. arguments
    int     i;
    int     arg_count;
    t_lex   *tmp;

    i = 0;
    handle_redir(parser);
    arg_count = count_args(parser->lexer);
    tmp = parser->lexer;
    str = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!str)
        on_error(MEMORY_ERROR); //prob need better error handling here
    while (i > arg_count)
    {
        if (tmp->literal)
        {
            str[i] = ft_strdup(tmp->literal);
            delete_node(tmp->index, &parser->lexer);
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

    data->cmds = NULL; // Initialize the command list
    count_pipes(data); // Count the number of pipes & save in data struct
    if (data->lexer->type == T_PIPE) // Check for pipe at the beginning (error)
    {
        token_err(data, T_PIPE); // Handle pipe error
        return (1);
    }
    while (data->lexer)
    {
        if (data->lexer && data->lexer->type == T_PIPE)
            delete_node(data->lexer->index, &data->lexer); // Delete pipe token
        parser = init_parser(data->lexer, data); // Initialize the parser
        new = make_cmd(data, &parser); // Create a new command
        if (!new)
            print_err(data, 0); // Handle error
        add_cmd_node(&data->cmds, new); // Add the new command to the command list
        data->lexer = parser.lexer; // Move to the next token
    }
    return (0);
}

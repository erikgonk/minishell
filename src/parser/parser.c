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

t_cmds *make_cmd(t_data *data, t_parser *parser)
{
    handle_redir(parser);
}

t_parser    init_parser(t_lex *lexer, t_data *data)
{
    t_parser    parser;

    parser.redirections = NULL;
    parser.data = data;
    parser.lexer = lexer;
    parser.redir_count = 0;
    return (parser);
}

int parser(t_data *data)
{
    t_parser parser;
    t_cmds  *new;

    data->cmds = NULL; // Initialize the command list
    count_pipes(data); // Count the number of pipes & save in data struct
    if (data->lexer->token == T_PIPE) // Check for pipe at the beginning (error)
    {
        token_err(data, T_PIPE); // Handle pipe error
        return (EXIT_FAILURE);
    }
    while (data->lexer)
    {
        if (data->lexer && data->lexer->token == T_PIPE)
            delete_node(data->lexer->index, &data->lexer); // Delete pipe token
        if (error_check(data))
            return(EXIT_FAILURE); // Check for errors
        parser = init_parser(data->lexer, data); // Initialize the parser
        new = make_cmd(data, &parser); // Create a new command
        if (!new)
            print_err(data, 0); // Handle error
        add_cmd_node(&data->cmds, new); // Add the new command to the command list
        data->lexer = parser.lexer; // Move to the next token
    }
    return (EXIT_SUCCESS);
}

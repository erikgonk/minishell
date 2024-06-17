/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:42:13 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/10 11:42:15 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * 1. Assigns new node to the redirection list with the
 * filename (or limiter in case of heredoc) and the 
 * type of redirection.
 * 2. Assigns the index of the nodes to be deleted
 * 3. Calls del_node functions to delete the two 
 * associated nodes from the lexer list
 * 4. Then increases the redirection count
*/
void    add_redir(t_parser *parser, t_lex *tmp)
{
    t_lex   *new;
    int     delete_index;

    new = lex_new_node(ft_strdup(tmp->next->literal), tmp->type);
    if (!new)
        return ;
    lex_add_node(&parser->redirections, new);
    parser->redir_count++;
    lex_del_node(delete_index, &parser->lexer);
    delete_index = delete_index + 1;
    lex_del_node(delete_index, &parser->lexer);
}

/**
 * 1. Iterates through the word tokens
 * 2. If end of string or a pipe (no more redirections), it returns
 * 3. If the token is a redirection token we call add_redir function
 * 4. Then we recursively call the function until no more redirection 
 * tokens are found
*/
void    handle_redirs(t_data *data, t_parser *parser)
{
    t_lex   *tmp;

    tmp = parser->lexer;
    while (tmp && tmp->type == T_WORD)
        tmp = tmp->next;
    if (!tmp || tmp->type == T_PIPE)
        return ;
    if (!tmp->next)
        on_error(data, SYNTAX_ERROR); //idk about error handling here
    if (tmp->next->type != T_WORD)
        token_error(data, tmp->next->type);
    if (tmp->type >= T_REDIR_IN && tmp->type <= T_APPEND)
        add_redir(parser, tmp);
    handle_redirs(data, parser);
}
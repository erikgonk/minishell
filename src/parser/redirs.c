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
void add_redir(t_parser *parser, t_lex *tmp)
{
    int     indx1;
    int     indx2;
    t_lex   *new;

    new = lex_new_node(ft_strdup(tmp->next->literal), tmp->type);
    if (!new)
        on_error();//error management
    lex_add_node()
    indx1 = tmp->index;
    indx2 = tmp->next->index;
    lex_del_node(&parser->lexer, indx1);
    lex_del_node(&parser->lexer, indx2);
    parser->redir_count++;
}

/**
 * 1. Iterates through the word tokens
 * 2. If end of string or a pipe (no more redirections), it returns
 * 3. If the token is a redirection token we call add_redir function
 * 4. Then we recursively call the function until no more redirection 
 * tokens are found
*/
void handle_redirs(t_parser *parser)
{
    t_lex *tmp;
 
    tmp = parser->lexer;
    while (tmp->type == T_WORD && tmp->type)
        tmp = tmp->next;
    if (!tmp || tmp->type == T_PIPE)
        return ;
    if (tmp->type >= T_REDIR_IN && tmp->type <= T_APPEND)
        add_redir(parser, tmp);
    handle_redirs(parser);
}
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

void    add_redir(t_parser *parser, t_lex *tmp)
{
    int     indx1;
    int     indx2;
    t_lex   *new;

    new = lex_add_node(ft_strdup(tmp->next->literal), tmp->type); //adds node that contains str name of file and the redirection type
    if (!new)
        on_error();//error management
    indx1 = tmp->index;
    indx2 = tmp->next->index;
    lex_del_node(&parser->lexer, indx1); //delete redir token node
    lex_del_node(&parser->lexer, indx2); //delete filename node
    parser->redir_count++; //add one to the redirection count
}

void    handle_redirs(t_parser *parser)
{
    t_lex *tmp;

    tmp = parser->lexer;
    while (tmp->type == T_WORD && tmp->type) // iterating through the word tokens
        tmp = tmp->next;
    if (!tmp || tmp->type == T_PIPE) // if we encounter a pipe or the end of the list we just return
        return ;
    if (tmp->type >= T_REDIR_IN && tmp->type <= T_APPEND)
        add_redir(parser, tmp); //add the redirection node to the redirection list
}
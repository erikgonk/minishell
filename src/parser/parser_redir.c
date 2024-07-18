/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:59:42 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/18 11:59:46 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

t_lex   *lex_new(char *str, int token)
{
    t_lex   *new;
    static int  i = 0;

    new = (t_lex *)malloc(sizeof(t_lex));
    if (!new)
        return (NULL);
    new->literal = ft_strdup(str);
    new->type = token;
    new->index = i++;
    new->next = NULL;
    return (new);
}

void    new_redir(t_lex *tmp, t_parser *parser)
{
    t_lex   *node;

    node = lex_new(tmp->next->literal, tmp->type);
    if (!node)
        return ;
    lex_lstaddback(&parser->redirections, node);
    lex_lstdelone(&parser->lexer, tmp->next->index);
    lex_lstdelone(&parser->lexer, tmp->index);
    parser->redir_count++;
}

void    add_redir(t_parser *parser)
{
    t_lex   *tmp;

    tmp = parser->lexer;
    while (tmp && tmp->type == T_WORD)
        tmp = tmp->next;
    if (!tmp || tmp->type == T_PIPE)
        return ;
    if (tmp->type >= T_REDIR_IN && tmp->type <= T_APPEND)
        new_redir(tmp, parser);
    add_redir(parser);
}

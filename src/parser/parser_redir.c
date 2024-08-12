/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:17:38 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 11:42:37 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/parser.h"

void	new_redir(t_lex *tmp, t_parser *parser)
{
	t_lex	*node;

	node = lex_new(tmp->next->literal, tmp->type);
	if (!node)
		return ;
	lex_addback(&parser->redirections, node);
	lex_delone(&parser->lexer, tmp->next->index);
	lex_delone(&parser->lexer, tmp->index);
	parser->redir_count++;
}

void	add_redir(t_parser *parser)
{
	t_lex	*tmp;

	tmp = parser->lexer;
	while (tmp && tmp->type == T_WORD)
		tmp = tmp->next;
	if (!tmp || tmp->type == T_PIPE)
		return ;
	if (tmp->type >= T_REDIR_IN && tmp->type <= T_APPEND)
		new_redir(tmp, parser);
	add_redir(parser);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:32:25 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 12:32:28 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define C_LESS '>'
# define C_GREAT '<'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '"'

enum e_token
{
	T_PIPE = 1,
	T_REDIR_OUT,
	T_APPEND,
	T_REDIR_IN,
	T_HEREDOC,
	T_WORD
};

typedef struct s_lex
{
	enum e_token	type;
	char			*literal;
	int				i;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;

#endif
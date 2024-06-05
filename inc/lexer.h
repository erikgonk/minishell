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

# define C_LESS '>'
# define C_GREAT '<'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '"'

typedef enum s_token
{
	T_PIPE = 1,
	T_LESS,
	T_LESSLESS,
	T_GREAT,
	T_GREATGREAT,
	T_WORD
}	t_token;


typedef struct s_lex
{
	t_token			type;
	char			*literal;
	int				i;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;
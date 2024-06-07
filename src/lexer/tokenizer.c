/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:11:09 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 12:11:21 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/lexer.h"

/**
* Declares the token list, iterates through whitespace. 
* Then it calls the token_length to find the length 
* then it will call fill_tokens to create the linked list
* with the input we received from our user. Lastly it will
* return the token list to the caller (main_loop)
*/
t_lex	*tokenizer(char *input)
{
	t_lex	*tokens;
	int		length;

	length = 0;
	tokens = NULL;
	while (*input)
	{
		if (*input == ' ' || (*input >= 8 && *input <= 13))
			input++;
		else
		{
			length = token_length(input);
			tokens = fill_tokens(tokens, input, length);
			input += length;
		}
	}
	return(tokens);
}

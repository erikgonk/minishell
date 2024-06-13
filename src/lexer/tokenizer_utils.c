/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:25:02 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 13:25:05 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void    add_index(t_lex *tokens)
{
    int i;

    i = 0;
    while (tokens)
    {
        tokens->index = i;
        tokens = tokens->next;
        i++;
    }
}

/**
* Will count the length of the characters between two 
* quotes. First checking which type of quote it is 
* (double or single), lastly returning the length.
*/
static int  quote_length(char *str)
{
    int length;
    char quote;

    quote = -1;
    length = 1;
    if (*str == C_SQUOTE)
        quote = C_SQUOTE;
    else 
        quote = C_DQUOTE;
    str++;
    while (*str)
    {
        length++;
        if (*str == quote)
            return (length);
        str++;
    }
    return (length);
}

/**
* Will check for special tokens first, because we know how they look. 
* If it is not a special or redir token, we iterate until a space or special token
* is met. Always checking for quotes and counting the inside of the quote if encountered
*/
int     token_length(char *input)
{
    int     length;
    int     add;

    length = 0;
    add = 1;
    if ((input[0] == C_LESS && input[1] == C_LESS) || (input[0] == C_GREAT && input[1] == C_GREAT))
        length = 2;
    else if (input[0] == C_PIPE ||input[0] == C_GREAT ||input[0] == C_LESS)
        length = 1;
    else
    {
        while (*input && *input != C_PIPE && *input != C_LESS && *input != C_GREAT && *input != ' ')
        {
            if (*input == C_SQUOTE ||*input == C_DQUOTE)
                add = quote_length(input);
            length += add;
            input += add;
        }
    }
    return (length);
}


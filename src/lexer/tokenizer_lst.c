/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:28:36 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 13:28:39 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/** 
* Just an utils function in case of errors since we are dealing
* with mallocated linked lists.
**/
void    free_tokens(t_lex *tokens)
{
    t_lex *tmp;

    if (!tokens)
        return ;
    while (tokens)
    {
        free(tokens->literal);
        tmp = tokens;
        tokens = tokens->next;
        free(tmp);
    }
    return ;
}

/**
* This funcion will simply just check which type of token we are dealing with. 
* If a special token, that is return, else, we assume it is a word.
*/
static int  find_type(char *literal)
{
    if ((literal[0] == C_LESS && literal[1] == C_LESS))
        return (T_HEREDOC);
    if ((literal[0] == C_GREAT && literal[1] == C_GREAT))
        return (T_APPEND);
    if (literal[0] == C_PIPE)
        return (T_PIPE);
    if (literal[0] == C_LESS)
        return (T_REDIR_IN);
    if (literal[0] == C_GREAT)
        return (T_REDIR_OUT);
    return (T_WORD);
}

/**
* Make token will allocate memory for the new node (token) in the
* char *literal part of the structure. 
* It will copy from the input to the literal and then null terminate the string. 
* Lastly it will assign the token type to the type. 
*/
static t_lex *make_token(int length, char *input)
{
    int i;
    t_lex *new;

    new = malloc(sizeof(t_lex));
    if (!new)
        return (NULL);
    new->literal = (char *)malloc(sizeof(char) * (length + 1));
    if (!new->literal)
    {
        free(new);
        return (NULL);
    }
    while (i < length)
    {
        new->literal[i] = input[i];
        i++;
    }
    new->literal[i] = '\0';
    new->next = NULL;
    new->type = find_type(new->literal);
    return (new);
}

/**
* Responsible for filling the token linked list. 
* 1. calls the make_token with current length and input
* 2. If the tokens list is empty, we set the new node as the first one.
* 3. If not, we add it to the back of the list by first iterating through it and
* then setting the new->prev to the last. 
*/
t_lex *fill_tokens(t_lex *tokens, char *input, int length)
{
    t_lex *last;
    t_lex *new;

    new = make_token(length, input);
    if (!new)
    {
        if (tokens)
            free_tokens(tokens);
        return (NULL);
    }
    if (tokens == NULL)
        tokens = new;
    else
    {
        last = tokens;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
    }
    return (tokens);
}

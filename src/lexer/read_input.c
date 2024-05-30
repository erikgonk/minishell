/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:29:25 by vaunevik          #+#    #+#             */
/*   Updated: 2024/05/30 13:29:37 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * 1. need function to skip whitespace
 * 2. nodeadd and addback functions for the linked list
 * 3. Read the words and check whether it is a token or a word
 **/

int     ft_isspace(char c)
{
    if (c == ' ' || (c > 8 && c < 14))
        return (1);
    return (0);
}

int    ft_skipspace(char *str, int i)
{
    int j;

    j = 0;
    while (ft_isspace(str[i + j]))
        j++;
    return(j);
}




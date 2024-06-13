/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:37:16 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/13 12:37:19 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_closed_quotes(char *str)
{
    int squote;
    int dquote;

    squote = 0;
    dquote = 0;
    while (*str)
    {
        if (*str == C_SQUOTE)
            squote++;
        if (*str == C_DQUOTE)
            dquote++;
        str++;
    }
    if (squote % 2 != 0)
        return (0);
    if (dquote % 2 != 0)
        return (0);
    return (1);
}

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

int check_inside_quotes(char *str, int index, int *counter, char *type)
{
    int i;

    i = index + 1;
    *counter += 1;
    while (str[i] && str[i] != type)
        i++;
    if (str[i] == type)
        *counter += 1;
    return (index - i);
}

int check_closed_quotes(char *str)
{
    int dble;
    int sgle;
    int i;

    i = 0;
    dble = 0;
    sgle = 0;
    while (str[i++])
    {
        if (str[i] == C_SQUOTE)
            i += check_inside_quotes(str, i, &sgle, C_SQUOTE);
        if (str[i] == C_DQUOTE)
            i += check_inside_quotes(str, i, &dble, C_DQUOTE);
    }
    if ((dble > 0 && dble % 2 != 0) || (sgle > 0 && sgle % 2 != 0))
        return (1);
    return (0);
}

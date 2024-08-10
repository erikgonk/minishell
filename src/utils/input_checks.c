/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:19:01 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/10 14:19:03 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/utils.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	change_flag(int flag)
{
	if (flag == 0)
		return (1);
	else
		return (0);
}

static int syntax_check(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == ';')
        {
            printf("mish: we don't do the ';' around here\n");
            return(1);
        }
        else if (input[i] == '\\')
        {
            printf("mish: we don't to the '\\' around here\n");
            return(1);
        }
        else if (input[i] == '|' && input[i + 1] == '|')
        {
            printf("mish: we don't do the '||' around here\n");
            return(1);
        }
        else if (input[i] == '&' && input[i + 1] == '&')
        {
            printf("mish: we don't do the '&&' around here\n");
            return(1);
        }
        else
            i++;
    }
    return (0);
}

int	quotes(char *input, int *i, int flag, char c)
{
	if (input[*i] == c)
	{
		flag = change_flag(flag);
		(*i)++;
		while (input[*i] && input[*i] != c)
			(*i)++;
		if (input[*i] == c)
		{
			flag = change_flag(flag);
			(*i)++;
		}
	}
	return (flag);
}

int	quote_checker(char *str)
{
	int	single_flag;
	int	double_flag;
	int	i;
	int	j;

	double_flag = 0;
	single_flag = 0;
	i = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		j = i;
		double_flag = quotes(str, &i, double_flag, '\"');
		single_flag = quotes(str, &i, single_flag, '\'');
		if (i == j)
			i++;
	}
	if (double_flag || single_flag)
		return(1);
    return (0);
}

int	arg_count(char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

/**
 * Just some checks to make sure the program does not crash
 * if the user decides to be annoying and input too many 
 * arguments or use open quotes.
*/
int input_check(char *input, t_data *data)
{
    if (quote_checker(input))
    {
        printf("minish: syntax error: open quotes\n");
        data->g_exit = 2;
        return (1);
    }
    if (syntax_check(input))
    {
        data->g_exit = 1;
        return (1);
    }
    if (arg_count(input, ' ') > 100) //idk how many arguments should be limit here 
    {
        printf("mish: don't be crazy: too many arguments\n");
        data->g_exit = 1;
        return (1);
    }
    if (ft_strlen(input) > 4096)
    {
        printf("mish: don't be annoying: the prompt is too long\n");
        data->g_exit = 1;
        return (1);
    }
    return (0);
}

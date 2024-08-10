/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:19:20 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/10 14:19:25 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/utils.h"

static int only_whitespace(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!ft_isspace((unsigned char)str[i]))
            return 0;
        i++;
    }
    return 1;
}

static void skip_whitespace_back(t_data *data)
{
    char *str;
    int i;

    if (data->input == NULL)
        return;
    i = ft_strlen(data->input);
    while (i > 0 && ft_isspace((unsigned char)data->input[i - 1]))
        i--;
    str = ft_substr(data->input, 0, i);
    free(data->input);
    data->input = str;
}

void skip_whitespace(t_data *data)
{
    char *str;
    int i;

    if (data->input == NULL)
        return ;
    i = 0;
    while (data->input[i] && ft_isspace((unsigned char)data->input[i]))
        i++;
    str = ft_substr(data->input, i, ft_strlen(data->input) - i);
    free(data->input);
    data->input = str;
    if (only_whitespace(data->input))
    {
        free(data->input);
        data->input = NULL;
        return ;
    }
    skip_whitespace_back(data);
}

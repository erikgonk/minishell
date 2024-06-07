/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:57:56 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/07 12:57:59 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// count pipes
void    count_pipes(t_data *data)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (data->input[i++])
    {
        if (data->input[i] == '|')
            count++;
    }
    data->pipes = count;
}

// count arguments


// check pipe error line

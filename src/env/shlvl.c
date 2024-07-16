/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:37:07 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/15 14:37:10 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "env.h"

void    add_shlvl(t_env *env)
{
    t_node  *tmp;
    int     value;

    tmp = env->start;
    while (tmp->next)
    {
        if (ft_strcmp(tmp->var, "SHLVL"))
        {
            value = ft_atoi(tmp->str);
            if (value > 1000)
            {
                ft_putstr_fd("minish: shlvl too high: resetting to 1", 2);
                tmp->str = ft_itoa("1");
            }
            if (value < 0)
                tmp->str = ft_itoa("0");
            else
            {
                value++;
                tmp->str = ft_itoa(value);
            }
        }
        tmp = tmp->next;
    }
}
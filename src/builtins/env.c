/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:31 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/20 12:43:06 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

void    ft_print_env(t_node env)
{
	while (env)
	{
		if (env->var && env->str)
			ft_printf("%s=%s", env->var, env->str, 1);
		env = env->next;
	}
}

int	ft_env(t_env env)
{
	if (!env->start || !env->start->var || !env->start->str)
	{
		ft_printf("env: not found", 1);
		return (1);
	}
	ft_print_env(env->start);
	return (0);
}

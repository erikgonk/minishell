/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:31 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/13 12:12:53 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

void	ft_print_env(t_node *env)
{
	while (env)
	{
		if (env->var && env->str)
		{
			ft_printf(1, "%s=%s\n", env->var, env->str);
		}
		env = env->next;
	}
}

int	ft_env(t_exec *exec)
{
	ft_print_env(exec->env_t->start);
	return (0);
}

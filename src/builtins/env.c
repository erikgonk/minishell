/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:31 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 10:53:08 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void    ft_print_env(t_node *env)
{
	while (env)
	{
		if (env->var && env->str)
			ft_printf("%s=%s\n", env->var, env->str, 1);
		env = env->next;
	}
}

int	ft_env(t_exec *exec)
{
	if (!exec->env_t->start || !exec->env_t->start->var || !exec->env_t->start->str)
	{
		ft_printf("minish: env: not found", 2);
		return (1);
	}
	ft_print_env(exec->env_t->start);
	return (0);
}

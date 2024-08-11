/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:31 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 15:30:06 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

void	ft_print_env(t_node *env)
{
	while (env)
	{
		if (env->var && env->str)
			ft_printf(2, "%s=%s\n", env->var, env->str);
		if (env->var && !env->str)
			ft_printf(2, "%s=\n", env->var);
		env = env->next;
	}
}

int	ft_env(t_exec *exec)
{
	if (!exec->env_t->start || !exec->env_t->start->var
		|| !exec->env_t->start->str)
	{
		ft_printf(2, "minish: env: not found");
		return (1);
	}
	ft_print_env(exec->env_t->start);
	return (0);
}

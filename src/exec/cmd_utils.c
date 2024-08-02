/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:06:33 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 11:52:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	ft_init_exec(t_exec *exec)
{
	exec->p[0] = 0;
	exec->p[1] = 1;
	exec->g_exit = 0;
}

int	ft_lst_size(t_cmds *cmd)
{
	int		i;

	i = -1;
	while (cmd && ++i > -42)
		cmd = cmd->next;
	return (i);
}

int	ft_count_list_elems_str(t_node *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if (env->str)
			i++;
		env = env->next;
	}
	return (i);
}

int	ft_env_to_cmd(t_node *env, t_exec *exec, int size, int i)
{
	char		*tmp;

	if (!env)
		return (1);
	exec->env = ft_calloc(size, sizeof(char *));
	while (env)
	{
		if (env->str)
		{
			tmp = ft_strjoin(env->var, "=");
			if (!tmp)
				return (1);
			exec->env[i] = ft_strjoin(tmp, env->str);
			if (!exec->env[i])
				return (free(tmp), ft_free_willy(exec->env), 1);
			free(tmp);
		}
		env = env->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/03 13:38:25 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static char	*ft_change_env_path(t_exec *exec, t_cmds *cmd, char *get)
{
	t_node		*aux;
	t_node		*env;
	char		*tmp;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		env = get_env_lst("PWD", exec->env_t->start);
		path = env->str;
	}
	aux = get_env_lst(get, exec->env_t->start);
	if (!aux)
		return (NULL);
	tmp = aux->str;
	aux->str = path;
	return (free(tmp), path);
}

int	ft_cd(t_exec *exec)
{
	char		*path;
	t_node		*tmp;

	ft_change_env_path(exec, exec->cmd_t, exec->env_t->oldpwd);
	if (!exec->cmd_t->cmd[1] || (exec->cmd_t->cmd[1][0] == '~'
		&& ft_strlen(exec->cmd_t->cmd[1]) == 1))
	{
		tmp = get_env_lst("HOME", exec->env_t->start);
		path = tmp->str;
	}
	else
		path = exec->cmd_t->cmd[1];
	if (!path)
	{
		ft_printf("mish: cd: HOME not set", 2);
		return (1);
	}
	if (exec->cmd_t->cmd[1][0] == '-')
	{
		chdir(path);
		return (0);
	}
	chdir(path);
	ft_change_env_path(exec, exec->cmd_t, exec->env_t->pwd);
	return (0);
}

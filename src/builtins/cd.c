/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 15:39:56 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static char	*ft_change_env_path(t_exec *exec, char *get)
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
	{
		ft_printf(2, "mish: cd: HOME not set\n");
		return (NULL);
	}
	tmp = aux->str;
	aux->str = path;
	return (free(tmp), path);
}

static char	*ft_cd_normi(t_exec *exec, char *path)
{
	t_node		*tmp;

	if (!exec->cmd_t->cmd[1] || (exec->cmd_t->cmd[1][0] == '~'
		&& ft_strlen(exec->cmd_t->cmd[1]) == 1))
	{
		tmp = get_env_lst("HOME", exec->env_t->start);
		path = tmp->str;
	}
	else
		path = exec->cmd_t->cmd[1];
	return (path);
}

int	ft_cd(t_exec *exec)
{
	char		*path;

	if (exec->cmd_t->cmd[2])
	{
		ft_printf(2, "minish: cd: too many arguments\n");
		return (1);
	}
	path = ft_change_env_path(exec, exec->env_t->oldpwd);
	if (!path)
		return (1);
	path = ft_cd_normi(exec, path);
	if (exec->cmd_t->cmd[1][0] == '-' && !exec->cmd_t->cmd[1][1])
	{
		chdir(path);
		return (0);
	}
	if (chdir(path) != 1)
	{
		ft_printf(2, "minish: cd: %s: No such file or directory\n",
			exec->cmd_t->cmd[1]);
		return (1);
	}
	ft_change_env_path(exec, exec->env_t->pwd);
	return (0);
}

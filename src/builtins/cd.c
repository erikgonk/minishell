/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/09 14:51:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"
/*
static char	*ft_change_env_path(t_exec *exec, char *get)
{
	t_node		*aux;
	t_node		*env;
	char		*tmp;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		env = ft_get_env_lst("PWD", exec->env_t->start);
		path = env->str;
	}
	aux = ft_get_env_lst(get, exec->env_t->start);
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
		tmp = ft_get_env_lst("HOME", exec->env_t->start);
		path = tmp->str;
	}
	else
		path = exec->cmd_t->cmd[1];
	return (path);
}*/


static int	ft_get_old_pwd(t_exec *exec, int flag)
{
	char		*old_pwd;
	t_node		*tmp;

	if (ft_strcmp(exec->cmd_t->cmd[1], "-") && exec->env_t->oldpwd)
	{
		chdir(exec->env_t->oldpwd);
		flag = 1;
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		tmp = ft_get_env_lst("OLDPWD", exec->env_t->start);
		if (tmp)
		{
			if (tmp->str)
				free(tmp->str);
			tmp->str = old_pwd;
		}
		if (exec->env_t->oldpwd)
			free(exec->env_t->oldpwd);
		exec->env_t->oldpwd = old_pwd;
	}
	if (flag == 1)
		return (free(old_pwd), 1);
	return (free(tmp), 0);
}

static int	ft_cd_user(t_exec *exec)
{
	t_node		*tmp;

	if (!chdir(exec->env_t->homedir))
		return (1);
	tmp = ft_get_env_lst("PWD", exec->env_t->start);
	if (tmp->str)
		free(tmp->str);
	tmp->str = exec->env_t->homedir;
	exec->env_t->pwd = exec->env_t->homedir;
	return (1);
}

int	ft_cd(t_exec *exec)
{
	char		*pwd;

/*
	if (exec->cmd_t->cmd[2])
	{
		printf("minish: cd: too many arguments\n");
		return (1);
	}
*/
// handles cd - & oldpwd
	if (ft_get_old_pwd(exec, 0)) 
		return (0);
// cd && cd ~
	else if ((!exec->cmd_t->cmd[1] && ft_cd_user(exec)) || ft_strcmp(exec->cmd_t->cmd[1], "~"))
		return (0);
	pwd = getcwd(NULL, 0);
// unset PWD && they are in a 
	if (!ft_get_env_lst("PWD", exec->env_t->start) || !chdir(exec->cmd_t->cmd[1]))
	{
		if (pwd)
			free(pwd);
		ft_printf(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
		return (1);// ver el error de esto
	}
	chdir(exec->cmd_t->cmd[1]);
	return (0);
}







/*
int	ft_cd(t_exec *exec)
{
	char		*path;
	if (exec->cmd_t->cmd[2])
	{
		printf("minish: cd: too many arguments\n");
		return (1);
	}
	if (exec->env_t->oldpwd)
	{
		path = ft_change_env_path(exec, exec->env_t->oldpwd);
		if (!path)
			return (1);
		path = ft_cd_normi(exec, path);
	}
	if (exec->cmd_t->cmd[1] &&
			exec->cmd_t->cmd[1][0] == '-' && !exec->cmd_t->cmd[1][1])
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
}*/

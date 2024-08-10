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

static int	ft_get_old_pwd(t_exec *exec, int flag)
{
	char		*old_pwd;
	t_node		*tmp;

	/*if (ft_strcmp(exec->cmd_t->cmd[1], "-") && exec->env_t->oldpwd)
	{
		chdir(exec->env_t->oldpwd);
		flag = 1;
	}*/
	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		printf("hola\n");
		tmp = ft_get_env_lst("OLDPWD", exec->env_t->start);
			if (tmp->str)
				printf("%s\n", tmp->str);
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

static int	ft_cd_normi(t_exec *exec, char *pwd)
{
	t_node		*tmp;

	if (chdir(exec->cmd_t->cmd[1]) == -1)
	{
		ft_printf(2, "minish: cd: %s: No such file or directory\n",
		exec->cmd_t->cmd[1]);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (exec->env_t->pwd)
		free(exec->env_t->pwd);
	exec->env_t->pwd = pwd;
	tmp = ft_get_env_lst("PWD", exec->env_t->start);
	if (tmp->str)
		free(tmp->str);
	tmp->str = pwd;
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
// cd - & oldpwd
	if (ft_get_old_pwd(exec, 0)) 
		return (0);
// cd && cd ~
	else if ((!exec->cmd_t->cmd[1] && ft_cd_user(exec)))
		return (0);
	pwd = getcwd(NULL, 0);
// unset PWD && they are in a 
	if (!ft_get_env_lst("PWD", exec->env_t->start) || !getcwd(NULL, 0))
	{
		if (pwd)
			free(pwd);
		ft_printf(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return (1);// ver el error de esto
	}
// normal cd
	if (ft_cd_normi(exec, pwd))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/14 12:16:29 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static int	ft_get_old_pwd(t_exec *exec, int flag)
{
	char		*old_pwd;
	t_node		*tmp;

	if ((exec->cmd_t->cmd[1] && ft_strcmp(exec->cmd_t->cmd[1], "-"))
		&& exec->env_t->oldpwd)
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
			tmp->str = ft_strdup(old_pwd);
		}
		if (exec->env_t->oldpwd)
			free(exec->env_t->oldpwd);
		exec->env_t->oldpwd = ft_strdup(old_pwd);
	}
	return (free(old_pwd), flag);
}

static int	ft_cd_user(t_exec *exec)
{
	t_node		*tmp;

	if (!chdir(exec->env_t->homedir))
		return (1);
	tmp = ft_get_env_lst("PWD", exec->env_t->start);
	if (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		tmp->str = ft_strdup(exec->env_t->homedir);
	}
	exec->env_t->pwd = ft_strdup(exec->env_t->homedir);
	return (1);
}

static int	ft_cd_normi(t_exec *exec)
{
	t_node		*tmp;
	char		*pwd;

	if (exec->cmd_t->cmd && chdir(exec->cmd_t->cmd[1]) == -1)
	{
		ft_printf(2, "minish: cd: %s: No such file or directory\n",
			exec->cmd_t->cmd[1]);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (exec->env_t->pwd)
		free(exec->env_t->pwd);
	exec->env_t->pwd = ft_strdup(pwd);
	tmp = ft_get_env_lst("PWD", exec->env_t->start);
	if (!tmp)
		return (0);
	if (tmp->str)
		free(tmp->str);
	tmp->str = ft_strdup(pwd);
	return (free(pwd), 1);
}

static int	ft_cmd_length(t_cmds *cmd)
{
	int		i;

	i = 0;
	while (cmd && cmd->cmd[i])
		i++;
	return (i);
}

int	ft_cd(t_exec *exec)
{
	char		*pwd;

	if (ft_cmd_length(exec->cmd_t) > 2)
	{
		printf("minish: cd: too many arguments\n");
		return (1);
	}
	if (ft_get_old_pwd(exec, 0))
		return (0);
	if (!exec->cmd_t->cmd[1] || (exec->cmd_t->cmd && exec->cmd_t->cmd[1]
			&& ft_strcmp(exec->cmd_t->cmd[1], "~")))
	{
		ft_cd_user(exec);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_just_a_printf();
		return (1);
	}
	free(pwd);
	if (ft_cd_normi(exec))
		return (0);
	return (1);
}

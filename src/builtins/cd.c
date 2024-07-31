/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/31 16:37:25 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static char	*ft_change_env_path(t_data *data, t_cmds *cmd, char *get)
{
	char		*path;
	t_node		*aux;
	char		*tmp;
	t_node		*env;

	path = getcwd(NULL, 0);
	if (!path)
	{
		env = get_env_lst("PWD", data->env->start);
		path = env->str;
	}
	aux = get_env_lst(get, data->env->start);
	if (!aux)
		return (NULL);
	tmp = aux->str;
	aux->str = path;
	return (free(tmp), path);
}

int	ft_cd(t_data *data)
{
	char		*path;
	t_node		*tmp;

	ft_change_env_path(data, data->cmds, data->env->old_pwd);
	if (!data->cmds->cmd[1] || (data->cmds->cmd[1][0] == '~' && ft_strlen(data->cmds->cmd[1]) == 1))
	{
		tmp = get_env_lst("HOME", data->env->start);
		path = tmp->str;
	}
	else
		path = data->cmds->cmd[1];
	if (!path)
	{
		ft_printf("mish: cd: HOME not set", 2);
		return (1);
	}
	if (data->cmds->cmd[1][0] == '-')
	{
		chdir(path);
		return (0);
	}
	chdir(path);
	ft_change_env_path(data, data->cmds, data->env->pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/21 15:18:20 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

char	*ft_change_env_path(t_cmds *cmd, char *get)
{
	char		*path;
	t_node		aux;
	char		*tmp;
	t_env		env;

	path = getcwd(NULL, 0);
	if (!path)
	{
		env = get_env_lst("PWD", data);
		path = end.str;
	}
	aux = get_env_lst(get, cmd->env.start);
	if (!aux)
		return ;
	tmp = aux->str;
	aux->str = path;
	return (free(tmp), path);
}

int	ft_cd(t_data *data, int i)
{
	char		*path;
	t_node		*tmp;

	ft_change_env_path(data->cmds, OLDPWD);
	if (!data->cmds.cmd[i + 1] || (data->cmds.cmd[i + 1] == '~' && ft_strlen(data->cmds.cmd[i + 1]) == 1))
	{
		tmp = get_env_lst("HOME", data);
		path = tmp.str;
	}
	else
		path = data->cmds.cmd[i + 1];
	if (!path)
	{
		ft_printf("mish: cd: HOME not set")
		return (1);
	}
	if (data->cmds.cmd[i + 1] == '-')
	{
		chdir(path);
		return (0);
	}
	chdir(path);
	ft_change_env_path(data->cmds, PWD);
	return (0);
}

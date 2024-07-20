/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/18 15:16:35 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

char	*ft_change_env_path(t_cmd *cmd, char *get)
{
	char		*path;
	t_node		aux;
	char		*tmp;

	path = getcwd(NULL, 0);
	aux = get_env_lst(get, cmd->env.start);
	if (!aux)
		return ;
	tmp = aux->str;
	aux->str = path;
	return (free(tmp), path);
}

int	ft_cd(t_cmd *aux, t_data data, int i)
{
	char		*path;
	t_node		*tmp;

	ft_change_env_path(aux, OLDPWD);
	if (!aux->cmd[i + 1] || (aux->cmd[i + 1] == '~' && !aux->cmd[i + 2]))
	{
		tmp = get_env_lst("HOME", data);
		path = tmp.str;
	}
	else
		path = aux->cmd[i + 1];
	if (!path)
	{
		ft_printf("mish: cd: HOME not set")
		return (1);
	}
	if (aux->cmd[i + 1] == '-')
	{
		chdir(path);
		return (0);
	}
	chdir(path);
	ft_change_env_path(aux, PWD);
	return (0);
}

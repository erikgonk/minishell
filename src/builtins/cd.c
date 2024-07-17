/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/17 19:52:52 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

void	ft_change_env_path(t_cmd *cmd, char *path, char *flag)
{
	if (ft_strncmp("HOME", flag, 4))
		// change to home
}

int	ft_cd(t_cmd *aux, t_data data)
{
	char		*path;

	if (ft_strncmp("~", aux->cmd[0], 4) || !aux->cmd[0][3])
		path = get_env("HOME", data);
	if (!path)
	{
		ft_printf("minish: cd: HOME not set")
		return (1);
	}
	else 
		ft_change_env_path(aux, path, "HOME");
	if (!ft_strncmp("~", aux->cmd[0], 4) || aux->cmd[0][3])
	{
		path = aux->cmd[0];
		*path += 3;
		ft_change_env_path(aux, path, path);
	}
	chdir(path);
	return (0);
}

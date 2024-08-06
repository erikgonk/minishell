/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:27:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 13:37:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"

void	ft_close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static int	ft_get_cmd_help(t_exec *exec, t_cmds *cmd, int i)
{
	char	*tmp;

	if (access(cmd->cmd[1], F_OK) != 0)
	{
		ft_printf("%s: %s: Permission denied", cmd[0], cmd[i], 2);
		exec->g_exit = 1;
		return (1);
	}
	tmp = ft_strjoin(exec->path[i], "/");
	if (!tmp)
		exit (127);
	free(exec->path[i]);
	exec->path[i] = ft_strjoin(tmp, cmd->cmd[0]);
	if (!exec->path[i])
		exit (127);
	return (free(tmp), 0);
}

char	*ft_get_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
	int			i;
	t_node		*lst;

	i = -1;
	if (access(cmd->cmd[0], X_OK) == 0)
		return (cmd->cmd[0]);
	lst = get_env_lst("PATH", data->env->start);
	if (!lst || !lst->str)
	{
		ft_printf("minish: %s: No such file or directory\n", cmd->cmd[0], 2);
		exit (127);
	}
	exec->path = ft_split(lst->str, ':');
	if (!exec->path)
		exit (127);
	while (exec->path[++i])
	{
		if (ft_get_cmd_help(exec, cmd, i) == 1)
			continue ;
		if (access(exec->path[i], X_OK) == 0)
			return (exec->path[i]);
	}
	ft_printf("minish: %s: No such file or directory\n", cmd->cmd[0], 2);
	exit (127);
}

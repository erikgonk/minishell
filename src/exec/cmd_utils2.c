/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:27:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 16:45:58 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"

void	ft_close_pipes(int fd[2])
{
	printf("Pipe : %d %d\n\n\n", fd[0], fd[1]);
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
}

static void	ft_get_cmd_normi(t_exec *exec, t_cmds *cmd, int i)
{
	char	*tmp;

	tmp = ft_strjoin(exec->path[i], "/");
	if (!tmp)
		exit (127);
	free(exec->path[i]);
	exec->path[i] = ft_strjoin(tmp, cmd->cmd[0]);
	free(tmp);
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
		ft_printf(2, "minish: %s: No such file or directory\n", cmd->cmd[0]);
		exit (127);
	}
	exec->path = ft_split(lst->str, ':');
	if (!exec->path)
		exit (127);
	while (exec->path[++i])
	{
		ft_get_cmd_normi(exec, cmd, i);
		if (access(exec->path[i], X_OK) == 0)
			return (exec->path[i]);
	}
	ft_printf(2, "minish: %s: No such file or directory\n", cmd->cmd[0]);
	exit (127);
}

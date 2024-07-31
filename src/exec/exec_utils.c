/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:27:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/31 16:00:20 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_get_cmd_help(t_exec *exec, t_cmds *cmd, int i)
{
	char	*tmp;

	tmp = ft_strjoin(exec->path[i], "/");
	if (!tmp)
		exit (127);
	free(exec->path[i]);
	exec->path[i] = ft_strjoin(tmp, cmd->cmd[0]);
	if (!exec->path[i])
		exit (127);
	free(tmp);
}

char	*ft_get_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
		int			i;

		i = -1;
        t_node  *lst;
		if (access(cmd->cmd[0], X_OK) == 0)
			return (cmd->cmd[0]);
        lst = get_env_lst("PATH", data->env->start);
        if (!lst || !lst->str)
        {
				ft_printf("bash: %s: No such file or directory\n", cmd->cmd[0], 2);
    			exit (127);
        }
		exec->path = ft_split(lst->str, ':');
		if (!exec->path)
			exit (127);
		while (exec->path[++i])
		{
			ft_get_cmd_help(exec, cmd, i);
			if (access(exec->path[i], X_OK) == 0)
				return (exec->path[i]);
			// I gotta check when you cannot access a file
		}
		ft_printf("bash: %s: No such file or directory\n", cmd->cmd[0], 2);
		exit (127);
}

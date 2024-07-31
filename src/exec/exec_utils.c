/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:27:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/31 11:39:43 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

char	*ft_get_cmd(t_data *data, t_cmds *cmd)
{
        t_node  *lst;
		if (access(cmd->cmd[0], X_OK) == 0)
			return (cmd->cmd[0]);
        lst = get_env_lst("PATH", data->env->start);
        if (!lst || !lst->str)
        {
                ft_printf("bash: %s: No such file or directory\n", cmd->cmd[1], 2);
                exit (127);
        }
        return (lst->str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/30 19:16:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	ft_middle_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
	exex->fd = dup(exec->p[0]);// reads info from file before
	close_pipes(exec->p);
	pipe(exec->p);// creates again p[0] & p[1]
	dup2(exec->fd, 0);// reads from fd (where the info has been saved)
	close(exec->fd);
	dup2(p[1], 1);// writes in the pipe
	close_pipes(exec->p);
}	

int	ft_innit_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
	if (!cmd->prev)
	{
		dup2(exec->p[1], 1);// writes in the pipe
		close_pipes(exec->p);
	}
	else if (cmd->next)
		ft_middle_cmd(data, cmd, exec);
	else
	{
		dup2(exec->p[0], 0);// writes in the pipe
		close_pipes(exec->p);
	}
}

int	ft_inni_builtin(t_data *data, t_cmds *cmd, t_exec *exec);

int	ft_childs(t_data *data, t_cmds *cmd, t_exec *exec)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (!cmd->cmd[0])
			exit (0);
		ft_innit_cmd(data, cmd, exex);
		if (cmd->builtin)
		{
			ft_inni_builtin(data, cmd, exec);
			exit (data->g_exit);
		}
		exec->cmd = ft_get_cmd(data, cmd);// error controled in the function
		exec->path = ft_get_path(data, cmd);
		execve(exec->cmd, exec->path, exec->env);
		exit (data->g_exit);
	}
	return (pid);
}

int	cmds(t_data *data, t_exec *exec)
{
	int		i;
	pid_t	*kids;// para buscar la salida del ultimo child
	t_cmds	*cmd;

	i = -1;
	kids = ft_calloc(ft_lst_size(data->cmds), sizeof(pid_t));
	if (!kids)
		return (1);
	ft_init_exec(exec);
	if (ft_env_to_cmd(data->env->start, exec, ft_count_list_elems_str(data->env->start), -1) == 1)// saves env in exec->env
		break ;// exit??? ---> mirar que hacer cuando la funcion de error
	while (cmd)
	{
		kids[++i] = ft_childs(data, cmd, exec);
		cmd = cmd->next;
	}
//	ft_find_exit_status(data, kids); --> data to count how many childs (cmds) are & kids to get it
	close_pipes(exec->p);
// free exec
	return (free(kids), data->g_exit);
}

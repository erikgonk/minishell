/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/01 17:19:10 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	ft_middle_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
	exec->fd = dup(exec->p[0]);// reads info from file before
	close_pipes(exec->p);
	pipe(exec->p);// creates again p[0] & p[1]
	dup2(exec->fd, 0);// reads from fd (where the info has been saved)
	close(exec->fd);
	dup2(exec->p[1], 1);// writes in the pipe
	close_pipes(exec->p);
}	

int	ft_forking(t_data *data, t_cmds *cmd, t_exec *exec)
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
		dup2(exec->p[0], 0);// writes in the terminal
		close_pipes(exec->p);
	}
	return (0);
}

int	ft_childs(t_data *data, t_cmds *cmd, t_exec *exec)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (!exec->cmd_t->cmd[0])
			exit (0);
		if (exec->cmd_t->redirections)
			ft_redirections(data, exec->cmd_t, exec);
		else if (exec->cmd_t->next)
			ft_forking(data, exec->cmd_t, exec);
		if (exec->cmd_t->builtin)
		{
			data->g_exit = ft_builtins(exec);
			exit (data->g_exit);
		}
		exec->cmd = ft_get_cmd(data, exec->cmd_t, exec);// error controled in the function
		execve(exec->cmd, exec->cmd_t->cmd, exec->env);
		exit (1);
	}
	return (pid);
}

void	ft_find_exit_status(t_data *data, pid_t *kids, int	size)
{
	int		res;
	int		status;
	int		i;
	pid_t	process;

	res = 0;
	status = 0;
	i = 0;
	while (i++ < size)
	{
		process = waitpid(-1, &status, 0);
		if (process == kids[size])
			res = status;
	}
	if (kids)
		free(kids);
	if (WEXITSTATUS(res))
		data->g_exit = WEXITSTATUS(res);
}

int	ft_cmds(t_data *data, t_exec *exec)
{
	int		i;
	pid_t	*kids;// to look for the exit status

	i = -1;
	kids = ft_calloc(ft_lst_size(data->cmds), sizeof(pid_t));
	if (!kids)
		return (1);
	ft_init_exec(exec);// initializes t_exec
	if (ft_env_to_cmd(data->env->start, exec, ft_count_list_elems_str(data->env->start), -1) == 1)
		exit (1);
	while (exec->cmd_t)
	{
		kids[++i] = ft_childs(data, exec->cmd_t, exec);
		exec->cmd_t = exec->cmd_t->next;
	}
	ft_find_exit_status(data, kids, (ft_lst_size(data->cmds) - 1));
	close_pipes(exec->p);
	return (free(kids), 0);
}

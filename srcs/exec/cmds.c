/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 13:32:44 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/redirs.h"

void	ft_middle_cmd(t_data *data, t_cmds *cmd, t_exec *exec)
{
	exec->fd = dup(exec->p[0]);// reads info from file before
	ft_close_pipes(exec->p);
	pipe(exec->p);// creates again p[0] & p[1]
	dup2(exec->fd, 0);// reads from fd (where the info has been saved)
	close(exec->fd);
	dup2(exec->p[1], 1);// writes in the pipe
	ft_close_pipes(exec->p);
}

int	ft_forking(t_data *data, t_cmds *cmd, t_exec *exec)
{
	if (!cmd->prev)
	{
		dup2(exec->p[1], 1);// writes in the pipe
		ft_close_pipes(exec->p);
	}
	else if (cmd->next)
		ft_middle_cmd(data, cmd, exec);
	else
	{
		dup2(exec->p[0], 0);// writes in the terminal
		ft_close_pipes(exec->p);
	}
	return (0);
}

int	ft_childs(t_data *data, t_cmds *cmd, t_exec *exec)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		if (!cmd->cmd[0])
			exit (0);
		if (cmd->redirections)
			ft_redirections(data, cmd, exec);
		else if (cmd->next)
			ft_forking(data, cmd, exec);
		if (cmd->builtin)
		{
			data->g_exit = ft_builtins(exec);
			exit (data->g_exit);
		}
		exec->cmd = ft_get_cmd(data, cmd, exec); // error controled in the function
		execve(exec->cmd, cmd->cmd, exec->env);
		exit (1);
	}
	return (pid);
}

void	ft_find_exit_status(t_data *data, pid_t *kids, int size)
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

int	ft_cmds(t_data *data, t_exec *exec, t_cmds *cmd)
{
	int		i;
	pid_t	*kids; // to look for the exit status

	i = -1;
	kids = ft_calloc(ft_lst_size(data->cmds), sizeof(pid_t));
	if (!kids)
		return (1);
	ft_init_exec(exec); // initializes t_exec
	if (ft_env_to_cmd(data->env->start, exec,
			ft_count_list_elems_str(data->env->start), -1) == 1)
	{
		exit (1);
	}
	while (cmd)
	{
		kids[++i] = ft_childs(data, cmd, exec);
		cmd = cmd->next;
	}
	ft_find_exit_status(data, kids, (ft_lst_size(data->cmds) - 1));
	ft_close_pipes(exec->p);
	return (free(kids), exec->g_exit);
}

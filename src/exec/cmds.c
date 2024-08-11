/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/11 11:35:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/redirs.h"
#include "../../inc/builtins.h"

static void	ft_middle_cmd(t_exec *exec)
{
	exec->fd = dup(exec->p[0]);// reads info from file before
	ft_close_pipes(exec->p);
	pipe(exec->p);// creates again p[0] & p[1]
}

static int	ft_forking(t_cmds *cmd, t_exec *exec)
{
	if (cmd->prev && cmd->next)
		ft_middle_cmd(exec);
	if (cmd->prev && cmd->in == 0)
	{
		if (cmd->next)
			dup2(exec->fd, 0);
		else
			dup2(exec->p[0], 0);// writes in the pipe
	}
	if (cmd->next && cmd->out == 1)
		dup2(exec->p[1], 1);// writes in the terminal
	ft_close_pipes(exec->p);
	if (exec->fd)
		close (exec->fd);
	return (0);
}

static int	ft_childs(t_data *data, t_cmds *cmd, t_exec *exec)
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
			ft_redirections(cmd);
		ft_forking(cmd, exec);
		if (ft_builtin_exists(exec) == 0)
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

static void	ft_find_exit_status(t_data *data, pid_t *kids, int size)
{
	int		res;
	int		status;
	int		i;
	pid_t	process;

	res = 0;
	status = 0;
	i = 0;
	while (i++ <= size)
	{
		process = waitpid(-1, &status, 0);
		if (process == kids[size])
			res = status;
	}
	if (WEXITSTATUS(res))
		data->g_exit = WEXITSTATUS(res);
}

int	ft_cmds(t_data *data, t_exec *exec)
{
	int		i;
	pid_t	*kids; // to look for the exit status

	i = -1;
	kids = ft_calloc(ft_lst_size(data->cmds), sizeof(pid_t));
	if (!kids)
		return (1);
	else if (ft_env_to_cmd(exec,
			ft_count_list_elems_str(data->env->start), -1) == 1)
		return (free(kids), 1);
	while (exec->cmd_t)
	{
		kids[++i] = ft_childs(data, exec->cmd_t, exec);
		exec->cmd_t = exec->cmd_t->next;
	}
	ft_close_pipes(exec->p);
	ft_free_willy(exec->env);
	ft_find_exit_status(data, kids, (ft_lst_size(data->cmds) - 1));
	return (free(kids), exec->g_exit);
}

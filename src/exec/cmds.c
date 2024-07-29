/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/29 19:07:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

static int	ft_lst_size(t_cmds *cmd)
{
	int		i;

	i = -1;
	while (cmd && ++i > -42)
		cmd = cmd->next;
	return (i);
}

int	ft_childs(t_data *data, int	fd, int pipe, char *kids)
{
	while (data->cmds)
	{

	}
}

void	ft_init_exec(t_exec *exec)
{
	exec->i = -1;
	exec->pipe[0] = 0;
	exec->pipe[1] = 1;
}

int	ft_redirs(t_data *data, t_exec *exec);

int	cmds(t_data *data, t_data)
{
	t_exec	exec;
	pid_t	*kids;
	t_cmds	*cmds;

	kids = (pid_t *)malloc(sizeof(pid_t) * ft_lst_size(data->cmds));
	if (!kids)
		return (1);
	ft_init_exec(&exec);
	while (cmds)
	{
		if (data->cmds->builtin && !data->cmds->redirections)
			pipex->err = ft_builtins(data);
		else if (data->cmds->redirections)
			ft_redirs(data, &exec);
		else
			data->g_exit = ft_childs(data, pipe, kids);
	}
	return (data->g_exit);
}





int	ft_start(t_data *data, t_exec *exec)
{
	exec.paths = ft_get_path(env);
	exec.fd = open(argv[1], O_RDONLY);
	if (exec.fd < 0)
		perror("argv[1]");
	if (pipe(exec.tube) < 0)
		perror("Pipe Function");
	exec.pid1 = fork();
	if (exec.pid1 == 0)
		child(exec, argv, env);
	waitpid(pipex.pid1, NULL, -1);
	close(exec.fd);
	exit (0);
}

char	*check_cmd(char **paths, char *argv)
{
	char		*tmp;
	char		*cmd;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd = ft_strjoin(tmp, argv);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		paths++;
	}
	return (NULL);
}

void	child(t_exec exec, char **argv, char **env)
{
	dup2(exec.tube[1], 1);
	close(exec.tube[0]);
	close(exec.tube[1]);
	dup2(exec.fd, 0);
	close(exec.fd);
	exec.cmd_args = ft_split(argv[2], ' ');
	if (exec.cmd_args[0] && (access(exec.cmd_args[0], X_OK) == 0))
		exec.cmd = exec.cmd_args[0];
	else
		exec.cmd = check_cmd(exec.paths, exec.cmd_args[0]);
	if (!exec.cmd)
		exit ((ft_fd_printf(2, "%s: cmd not found\n", argv[2]) * 0) + 1);
	execve(exec.cmd, exec.cmd_args, env);
}

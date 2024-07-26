/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/25 12:40:55 by erigonza         ###   ########.fr       */
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

int	cmds(t_data *data)
{
	int		fd;
	int		pipe[2];
	t_exec	*exec;
	pid_t	*kids;

	fd = -1;
	pipe[0] = -1;
	pipe[1] = -1;
	kids = (pid_t *)malloc(sizeof(pid_t) * ft_lst_size(data->cmds));
	if (!kids)
		return (1);
	// here doc
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

static char	**ft_get_path(char **e)
{
	char		**res;
	int			i;

	i = -1;
	while (e[++i] && ft_strncmp("PATH", e[i], 4))
	{
		if (!e[i + 1])
			perror(e[i]);
	}
	res = ft_split(e[i], ':');
	*res += 5;
	return (res);
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

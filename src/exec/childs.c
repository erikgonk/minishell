/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:54:07 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/12 11:21:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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

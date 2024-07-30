/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/30 17:05:45 by erigonza         ###   ########.fr       */
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

int	ft_childs(t_data *data, int	fd, int pipe, char *kids);
int	ft_builtins(t_data *data);

int	ft_count_list_elems_str(t_node *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if (env->str)
			i++;
		env = env->next;
	}
	return (i);
}

int	ft_env_to_cmd(t_node *env, t_exec *exec, int size, int i)
{
	char		*tmp;

	if (!env)
		return (1);
	exec->env = ft_calloc(size, sizeof(char *));
	while (env)
	{
		if (env->str)
		{
			tmp = ft_strjoin(env->var, "=");
			if (!tmp)
				return (1);
			exec->env[i] = ft_strjoin(tmp, env->str);
			if (!exec->env[i])
				return (free(tmp), ft_free_willy(exec->env), 1);
			free(tmp);
		}
		env = env->next;
	}
	return (0);
}

void	ft_init_exec(t_exec *exec)
{
	exec->i = -1;
	exec->pipe[0] = 0;
	exec->pipe[1] = 1;
}

int	cmds(t_data *data, t_exec *exec)
{
	pid_t	*kids;
	t_cmds	*cmds;

	kids = ft_calloc(ft_lst_size(data->cmds), sizeof(pid_t));
	if (!kids)
		return (1);
	ft_init_exec(exec);
	while (cmds)
	{
		if (ft_env_to_cmd(data->env->start, exec, ft_count_list_elems_str(data->env->start), -1) == 1)
			break ;// mirar que hacer cuando la funcion de error
		if (data->cmds->builtin && !data->cmds->redirections)
			data->g_exit = ft_builtins(data);
		else
			data->g_exit = ft_childs(data, pipe, kids);
	}
	free(kids);
// free exec
	return (data->g_exit);
}




/*
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
}*/

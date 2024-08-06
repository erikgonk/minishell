/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 19:06:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/redirs.h"

int	ft_builtins(t_exec *exec)
{
	static char		*bts[] = {"pwd", "echo", "cd", "export",
		"unset", "env", "exit", NULL};
	static int		(*builtins[])(t_exec *) = {ft_pwd, ft_echo,
		ft_cd, ft_export, ft_unset, ft_env, ft_exit};
	int				i;

	i = 0;
	while (bts[i] && ft_strcmp(bts[i], exec->cmd_t->cmd[0]))
		i++;
	if (bts[i])
		builtins[i](exec);
	else
		return (127);
	return (exec->g_exit);
}

static int	ft_builtin_exists(t_exec *exec)
{
	static char		*bts[] = {"pwd", "echo", "cd", "export",
		"unset", "env", "exit", NULL};
	int				i;

	i = 0;
	while (bts[i] && ft_strcmp(bts[i], exec->cmd_t->cmd[0]))
		i++;
	if (bts[i])
		return (0);
	return (1);
}

int	ft_executor(t_data *data, t_exec *exec, t_cmds *cmd)
{
	if (!exec->cmd_t->cmd)
		return (exec->g_exit);
	else if (!exec->cmd_t->next && ft_builtin_exists(exec) == 0
		&& !exec->lexer)
	{
		data->g_exit = ft_builtins(exec); // already exits
		return (data->g_exit);
	}
//	if (heredoc)
//		ft_heredoc(exec);
	while (cmd) // opening all fds
	{
		if (cmd->redirections)
			ft_inni_redirs(cmd->redirections);
		cmd = cmd->next;
	}
	data->g_exit = ft_cmds(data, exec);
	ft_free_willy(exec->env);
	ft_free_willy(exec->path);
	return (data->g_exit);
}

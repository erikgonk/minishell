/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/01 17:31:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

static int	ft_builtins(t_exec *exec)
{
//	static char		**builtins = {"pwd", "echo", "cd", "export", "unset", "env", "exit"};
	if (ft_strcmp("pwd", data->cmds->cmd[0]) == 0)
		exec->g_exit = ft_pwd(exec);
	else if (ft_strcmp("echo", data->cmds->cmd[0]) == 0)// NOT DONE YET
		exec->g_exit = ft_echo(exec);
	else if (ft_strcmp("cd", data->cmds->cmd[0]) == 0)
		data->g_exit = ft_cd(exec);
	else if (ft_strcmp("export", data->cmds->cmd[0]) == 0)
		data->g_exit = ft_export(exec);
	else if (ft_strcmp("unset", data->cmds->cmd[0] == 0))
		data->g_exit = ft_unset(exec);
	else if (ft_strcmp("env", data->cmds->cmd[0] == 0))
		data->g_exit = ft_env(exec);
	else if (ft_strcmp("exit", data->cmds->cmd[0] == 0))// NOT DONE YET
		data->g_exit = ft_exit(exec);
	else
		return (127);
	exit (data->g_exit);
}

int	ft_executor(t_exec	*exec)
{
	if (!exec->cmd_t->next && exec->cmd_t->builtin != NO_BUILTIN && !exec->lexer)
		exec->g_exit = ft_builtins(exec);// already exits
//	if (heredoc)
//		ft_heredoc(exec);
// open all redirs
	ft_cmds(exec, exec->cmd_t, &exec);
	ft_free_willy(exec.env);
	ft_free_willy(exec.path);
	return (exec->g_exit);
}

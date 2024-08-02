/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 17:14:00 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/redirs.h"

int	ft_builtins(t_exec *exec)
{
//	static char		**builtins = {"pwd", "echo", "cd", "export", "unset", "env", "exit"};
	if (ft_strcmp("pwd", exec->cmd_t->cmd[0]) == 0)
		exec->g_exit = ft_pwd(exec);
	else if (ft_strcmp("echo", exec->cmd_t->cmd[0]) == 0)// NOT DONE YET
		exec->g_exit = ft_echo(exec);
	else if (ft_strcmp("cd", exec->cmd_t->cmd[0]) == 0)
		exec->g_exit = ft_cd(exec);
	else if (ft_strcmp("export", exec->cmd_t->cmd[0]) == 0)
		exec->g_exit = ft_export(exec);
	else if (ft_strcmp("unset", exec->cmd_t->cmd[0] == 0))
		exec->g_exit = ft_unset(exec);
	else if (ft_strcmp("env", exec->cmd_t->cmd[0] == 0))
		exec->g_exit = ft_env(exec);
	else if (ft_strcmp("exit", exec->cmd_t->cmd[0] == 0))// NOT DONE YET
		exec->g_exit = ft_exit(exec);
	else
		return (127);
	return (exec->g_exit);
}

int	ft_executor(t_data *data, t_exec *exec, t_cmds *cmd)
{
	if (!exec->cmd_t->cmd)
		return (exec->g_exit);
	else if (!exec->cmd_t->next && exec->cmd_t->builtin != NO_BUILTIN && !exec->lexer)
		data->g_exit = ft_builtins(exec);// already exits
//	if (heredoc)
//		ft_heredoc(exec);
	while (cmd)// opening all fds
	{
		if (cmd->redirections)
			ft_inni_redirs(cmd->redirections);
		cmd = cmd->next;
	}
	data->g_exit = ft_cmds(data, exec, cmd);
	ft_free_willy(exec->env);
	ft_free_willy(exec->path);	
	return (data->g_exit);
}

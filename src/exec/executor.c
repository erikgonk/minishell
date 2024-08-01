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

static int	ft_builtins(t_data *data, t_cmds *cmd)
{
//	static char		**builtins = {"pwd", "echo", "cd", "export", "unset", "env", "exit"};
	if (ft_strcmp("pwd", data->cmds->cmd[0]) == 0)
		data->g_exit = ft_pwd(data);
	else if (ft_strcmp("echo", data->cmds->cmd[0]) == 0)// NOT DONE YET
		data->g_exit = ft_echo(data);
	else if (ft_strcmp("cd", data->cmds->cmd[0]) == 0)
		data->g_exit = ft_cd(data);
	else if (ft_strcmp("export", data->cmds->cmd[0]) == 0)
		data->g_exit = ft_export(data);
	else if (ft_strcmp("unset", data->cmds->cmd[0] == 0))
		data->g_exit = ft_unset(data);
	else if (ft_strcmp("env", data->cmds->cmd[0] == 0))
		data->g_exit = ft_env(data);
	else if (ft_strcmp("exit", data->cmds->cmd[0] == 0))// NOT DONE YET
		data->g_exit = ft_exit(data);
	else
		return (127);
	exit (data->g_exit);
}

int	ft_executor(t_data	*data)
{
	t_exec		exec;
	if (!data->cmds->next && data->cmds->builtin != NO_BUILTIN && !data->lexer)
		data->g_exit = ft_builtins(data, data->cmds);// already exits
//	if (heredoc)
//		ft_heredoc(data);
// open all redirs
	ft_cmds(data, data->cmds, &exec);
	ft_free_willy(exec.env);
	ft_free_willy(exec.path);
	return (data->g_exit);
}

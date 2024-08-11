/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/10 17:03:13 by erigonza         ###   ########.fr       */
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
	while (bts[i] && !ft_strcmp(bts[i], exec->cmd_t->cmd[0]))
		i++;
	if (bts[i])
		builtins[i](exec);
	else
		return (127);
	return (exec->g_exit);
}

int	ft_builtin_exists(t_exec *exec)
{
	static char		*bts[] = {"pwd", "echo", "cd", "export",
		"unset", "env", "exit", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strcmp(bts[i], exec->cmd_t->cmd[0]))
		i++;
	if (bts[i])
		return (0);
	return (1);
}

int	ft_executor(t_data *data, t_exec *exec)
{
	if (!exec->cmd_t->cmd)
		return (exec->g_exit);
	else if (exec->cmd_t->cmd && !exec->cmd_t->cmd[0])
		return (1);
	else if (exec->cmd_t->redirections)
		exec->lexer = data->cmds->redirections;
	if (ft_builtin_exists(exec) == 0 && !exec->lexer && !exec->cmd_t->next)
	{
		data->g_exit = ft_builtins(exec);
		return (data->g_exit);
	}
	ft_innit_redirs(exec->cmd_t);
	data->g_exit = ft_cmds(data, exec);
	return (data->g_exit);
}

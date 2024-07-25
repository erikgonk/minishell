/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/25 17:56:53 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

typedef struct s_childs
{
	pid_t			pid1;
	int				fd;
	int				tube[2];
	struct t_childs	*next;
}	t_childs;

typedef struct s_exec
{
	char		*cmd;
	char		**path;
	s_childs	*childs;
	int			i;
	int			err_status;
}	t_exec;

static int	ft_builtins(t_data *data);
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
	else if ("unset", data->cmds->cmd[0] == 0)
		data->g_exit = ft_unset(data);
	else if ("env", data->cmds->cmd[0] == 0)
		data->g_exit = ft_env(data);
	else if ("exit", data->cmds->cmd[0] == 0)// NOT DONE YET
		data->g_exit(data);
	else
		return (127);
	return (data->g_exit);
}

int	ft_executor(t_data	*data, t_exec *exec)
{
	if (!data->cmds->next && data->cmds->builtin && data->cmds->redirections)
		err = ft_builtins(data);
	while (data->cmds)
	{
		if (!data->cmds->cmd || !data->cmds->cmd[exec->i])	
			return (0);
		else
			data->g_exit = ft_cmds(data, exec);
		data->cmds = data->cmds->next;
	}
		return (data->g_exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/23 19:22:13 by erigonza         ###   ########.fr       */
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

int	ft_no_pipe_redir(t_data *data, t_exec *exec)
{
	if (data->)
}

int	ft_executor(t_data	*data, t_exec *exec)
{
	static int	err;

	err = 0;
// have a static varibale that she is passing me
	if (!data->cmds->cmd || !data->cmds->cmd[exec->i])	
		return (0);
	else if (!data->cmds->next)
		err = ft_no_pipe_redir(data, exec);
	else if (!no_pipe)
		err = ft_no_pipe(data, exec);
	else
		err = ft_pipe(data, exec);
	return (err);
}

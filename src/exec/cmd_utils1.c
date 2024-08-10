/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:06:33 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 16:03:41 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"

void	ft_init_exec(t_exec *exec, t_data *data)
{	
	pipe(exec->p);
	exec->g_exit = 0;
	exec->fd = 0;
	if (data->cmds)
		exec->lexer = data->cmds->redirections;
	else
		exec->lexer = NULL;
	exec->cmd_t = data->cmds;
	exec->env_t = data->env; 
}

int	ft_lst_size(t_cmds *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

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

int	ft_env_to_cmd(t_exec *exec, int size, int i)
{
	char		*tmp;
	t_node		*lst;

	lst = exec->env_t->start;
	if (!lst)
		return (1);
	exec->env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!exec->env)
		return (1);
	while (lst)
	{
		if (lst->str)
		{
			tmp = ft_strjoin(lst->var, "=");
			if (!tmp)
				return (1);
			exec->env[++i] = ft_strjoin(tmp, lst->str);
			if (!exec->env[i])
				return (free(tmp), 1); //free willy of env taken out of here
			free(tmp);
		}
		lst = lst->next;
	}
	exec->env[size] = NULL;
//	printf("hola\n");
	return (0);
}

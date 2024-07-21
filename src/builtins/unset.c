/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/21 16:27:52 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static t_node	*get_env_before_lst(char *to_find, t_env *aux)
{
	int		i;
	int		j;

	i = ft_strlen(to_find);
	j = ft_strlen(aux->start.next.var);
	if (i != j)
		return (NULL);
	else if (aux->start && ft_strncmp(to_find, aux->start.var, i) == 0)
		return (aux->start);
	else if (aux && ft_strncmp(to_find, aux->end.var, i) == 0)
		return (aux.end);
	while (aux->start.next)
	{
		if (ft_strncmp(to_find, aux->start.next.var, i) == 0)
			return (aux->start);
		aux = aux->start.next;
	}
	return (NULL);
}

int	ft_unset(t_data *cmd, int i)
{
	t_node		*node = NULL;
	int			err;

	node = get_env_before_lst(cmd->cmds.cmd[1], cmd->env);
	err = 0;
	if (cmd->cmds.cmd[2])	
		return (free(node), 0);
	err = ft_delete_node(cmd->env, node->var)
}

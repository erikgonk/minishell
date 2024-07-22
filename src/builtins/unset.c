/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/21 18:13:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static t_node	*ft_get_env_before_lst(char *to_find, t_env *aux)
{
	int		i;
	int		j;

	i = ft_strlen(to_find);
	j = ft_strlen(aux->start->next->var);
	if (i != j)
		return (NULL);
	else if (aux->start && ft_strncmp(to_find, aux->start->var, i) == 0)
		return (aux->start);
	else if (aux && ft_strncmp(to_find, aux->end->var, i) == 0)
		return (aux->end);
	while (aux->start->next)
	{
		if (ft_strncmp(to_find, aux->start->next->var, i) == 0)
			return (aux->start);
		aux = aux->start->next;
	}
	return (NULL);
}

int	ft_unset(t_data *cmd, int i)
{
	int			err;
	t_node		*node = NULL;
	t_node		*node_bef = NULL;

	err = 0;
	node_bef = ft_get_env_before_lst(cmd->cmds->cmd[i + 1], cmd->env);
	node = get_env_lst(cmd->cmds->cmd[i + 1], cmd->env);
	if (!node_bef || !node)	
		return (0);
	if (ft_get_env_before_lst(node->var, node_bef->var))// edge case being the first variable START
	{
		t_data->env->start = node->next;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	else if (!node->next)// edge case being the last variable END
	{
		t_data->env->end = node_bef;
		node_bef->next = NULL;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	node_bef->next = node->next;
	if (node->str)
		free(node->str);
	return (free(node->var), free(node), 0);
}

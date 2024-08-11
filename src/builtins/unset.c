/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/09 12:34:05 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static t_node	*ft_get_env_before_lst(char *to_find, t_node *lst, t_exec *exec)
{
	if (!to_find)
		return (NULL);
	if (lst && ft_strcmp(to_find, lst->var) != 0)
		return (exec->env_t->start);
	else if (lst && ft_strcmp(to_find, exec->env_t->end->var) != 0)
		return (exec->env_t->end);
	while (lst->next)
	{
		if (ft_strcmp(to_find, lst->next->var) != 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static int	ft_extra_unset(t_exec *exec, t_node *node, t_node *node_bef)
{
	if (ft_strcmp(exec->env_t->start->var, node->var) == 0)
		return (1);
	else if (!node->next) // edge case being the last variable END
	{
		exec->env_t->end = node_bef;
		node_bef->next = NULL;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	else if (ft_get_env_before_lst(node->var, node_bef, exec)) // edge case being the first variable START
	{
		exec->env_t->start = node->next;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	return (1);
}

static void	ft_freeing(t_node *node)
{
	free(node->var);
	if (node->str)
		free(node->str);
	free(node);
}

int	ft_unset(t_exec *exec)
{
	t_node		*node;
	t_node		*node_bef;
	int			i;

	i = 0;
	if (!exec->cmd_t->cmd[1])
		return (0);
	while (exec->cmd_t->cmd[++i])
	{
		node_bef = ft_get_env_before_lst(exec->cmd_t->cmd[i],
				exec->env_t->start, exec);
		node = ft_get_env_lst(exec->cmd_t->cmd[i], exec->env_t->start);
		if (!node_bef || !node)
			continue ;
		else if (ft_extra_unset(exec, node, node_bef) == 0)
			continue ;
		node_bef->next = node->next;
		if (node)
			ft_freeing(node);
	}
	return (0);
}

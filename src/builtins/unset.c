/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 14:13:42 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static t_node	*ft_get_env_before_lst(char *to_find, t_node *lst, t_exec *exec)
{
	if (exec->env_t->start && !exec->env_t->start->next)
		return (NULL);
	if (!to_find)
		return (NULL);
	if (lst && ft_strcmp(to_find, lst->var) != 0)
		return (exec->env_t->start);
	else if (exec->env_t->end && lst && ft_strcmp(to_find, exec->env_t->end->var) != 0)
		return (exec->env_t->end);
	while (lst && lst->next)
	{
		if (ft_strcmp(to_find, lst->next->var) != 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static void	ft_extra_extra_unset(t_exec *exec, t_node *node, t_node *node_bef)
{
	if (exec->env_t->start && !exec->env_t->start->next)
	{
		exec->env_t->start = NULL;
		exec->env_t->end = NULL;
	}
	if (exec->env_t->start && exec->env_t->start->next && !exec->env_t->start->next->next && !node_bef)
	{
		exec->env_t->start = node;
		exec->env_t->end = node;
		node->next = NULL;
	}
}

static int	ft_extra_unset(t_exec *exec, t_node *node, t_node *node_bef)
{
	if (exec->env_t->start && ft_strcmp(exec->env_t->start->var, node->var) == 0)
		return (1);
	if (ft_get_env_before_lst(node->var, node_bef, exec)) // edge case being the first variable START
	{
		if (node->next)
			exec->env_t->start = node->next;
		ft_extra_extra_unset(exec, node, node_bef);
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	if (!node->next) // edge case being the last variable END
	{
		exec->env_t->end = node_bef;
		node_bef->next = NULL;
		if (node && node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	return (1);
}

static void	ft_freeing(t_node *node)
{
	if (node->str)
		free(node->str);
	if (node->var)
		free(node->var);
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
		if (ft_extra_unset(exec, node, node_bef) == 0)
			continue ;
		if (node->next)
			node_bef->next = node->next;
		if (node)
			ft_freeing(node);
	}
	return (0);
}

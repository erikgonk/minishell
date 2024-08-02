/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 15:22:38 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

t_node  *get_env_lst(char *to_find, t_node *lst)
{
        while (lst)
        {
                if (ft_strcmp(to_find, lst->var) == 0)
					return (lst);
                lst = lst->next;
        }
        return (NULL);
}

static t_node	*ft_get_env_before_lst(char *to_find, t_node *lst, t_node *env, t_exec *exec)
{
	if (!to_find)
		return (NULL);
	if (lst && ft_strcmp(to_find, lst->var) == 0)
		return (exec->env_t->start);
	else if (lst && ft_strcmp(to_find, exec->env_t->end->var) == 0)
		return (exec->env_t->end);
	while (lst->next)
	{
        if (ft_strcmp(to_find, lst->next->var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	**ft_free_willy(char **split)
{
	int		i;

	i = -1;
	if (!split)
		return (NULL);
	while (split[++i])
		free(split[i]);
	free(split);
	return (0);
}

static int	ft_extra_unset(t_exec *exec, t_node *node, t_node *node_bef)
{
	if (ft_get_env_before_lst(node->var, node_bef, exec->env_t->start, exec))// edge case being the first variable START
	{
		exec->env_t->start = node->next;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	else if (!node->next)// edge case being the last variable END
	{
		exec->env_t->end = node_bef;
		node_bef->next = NULL;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	return (1);
}

int	ft_unset(t_exec *exec)
{
	t_node		*node = NULL;
	t_node		*node_bef = NULL;

	node_bef = ft_get_env_before_lst(exec->cmd_t->cmd[1], exec->env_t->start, exec->env_t->start, exec);
	node = get_env_lst(exec->cmd_t->cmd[1], exec->env_t->start);
	if (!node_bef || !node)	
		return (1);
	else if (ft_extra_unset(exec, node, node_bef) == 0)
		return (0);
	node_bef->next = node->next;
	if (node->str)
		free(node->str);
	return (0);
}

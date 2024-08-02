/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 10:54:18 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"
#include "../../inc/exec.h"

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

static t_node	*ft_get_env_before_lst(char *to_find, t_node *lst, t_node env)
{
	if (!to_find)
		return (NUL);
	if (lst && ft_strcmp(to_find, lst->var) == 0)
		return (aux->start);
	else if (lst && ft_strcmp(to_find, aux->end->var) == 0)
		return (aux->end);
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

static int	ft_extra_unset(t_exec *exec, t_node *node, t_node node_bef)
{
	if (ft_get_env_before_lst(node->var, node_bef->var, cmd->env))// edge case being the first variable START
	{
		exev->env_t->start = node->next;
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
	int			err;
	t_node		*node = NULL;
	t_node		*node_bef = NULL;

	err = 0;
	node_bef = ft_get_env_before_lst(exec->cmd_t->cmd[1], exec->env_t->start, exec->env_t);
	node = get_env_lst(exec->cmd_t->cmd[1], exec->env_t->start);
	if (!node_bef || !node)	
		return (0);
	else if (ft_extra_unset(exec, node, node_bef) == 0)
		return (0);
	node_bef->next = node->next;
	if (node->str)
		free(node->str);
	return (free(node->var), free(node), 0);
}

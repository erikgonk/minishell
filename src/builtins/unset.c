/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/23 12:35:20 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

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

static char	**ft_free_willy(char **split)
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

static int	ft_extra_unset(t_data *data, t_node *node, t_node node_bef)
{
	if (ft_get_env_before_lst(node->var, node_bef->var, cmd->env))// edge case being the first variable START
	{
		data->env->start = node->next;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	else if (!node->next)// edge case being the last variable END
	{
		data->env->end = node_bef;
		node_bef->next = NULL;
		if (node->str)
			free(node->str);
		return (free(node->var), free(node), 0);
	}
	return (1);
}

int	ft_unset(t_data *cmd, int i)
{
	int			err;
	t_node		*node = NULL;
	t_node		*node_bef = NULL;

	err = 0;
	node_bef = ft_get_env_before_lst(cmd->cmds->cmd[i + 1], cmd->env->start, cmd->env);
	node = get_env_lst(cmd->cmds->cmd[i + 1], cmd->env->start);
	if (!node_bef || !node)	
		return (0);
	else if (ft_extra_unset(data, node, node_bef) == 0)	{
		return (0);
	node_bef->next = node->next;
	if (node->str)
		free(node->str);
	return (free(node->var), free(node), 0);
}

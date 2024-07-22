/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:46:30 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/22 16:31:25 by erigonza         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (lst && ft_strcmp(to_find, lst->var) == 0)
		return (aux->start);
	else if (lst && ft_strcmp(to_find, aux->end->var) == 0)
		return (aux->end);
	while (lst->next)
	{
		while (to_find)
		{
			if ((!to_find[i] && lst->next->var[i]) || (to_find[i] && !lst->next->var[i]))
				break ;
			else if ()
				break ;
			else if ()
				return ()
			i++;
		}
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
	node_bef = ft_get_env_before_lst(cmd->cmds->cmd[i + 1], cmd->env->start, cmd->env);
	node = get_env_lst(cmd->cmds->cmd[i + 1], cmd->env->start);
	if (!node_bef || !node)	
		return (0);
	else if (ft_get_env_before_lst(node->var, node_bef->var, cmd->env))// edge case being the first variable START
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:44:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/09 14:12:29 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

char	**ft_free_willy(char **cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
		if (!cmd[i + 1])
			break ;
	}
	free(cmd);
	cmd = NULL;
	return (0);
}

t_node	*ft_get_env_lst(char *to_find, t_node *lst)
{
	if (!lst || !to_find)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp(to_find, lst->var) != 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

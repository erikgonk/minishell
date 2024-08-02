/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:08:45 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 11:47:42 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static char	**ft_swap(char **list, int pos, int i)
{
	char	*tmp = NULL;

	while (list[++i])
	{
		if (list[i] > list[pos])
		{
			tmp = list[i];
			list[i] = list[pos];
			list[pos] = tmp;	
			return (free(tmp), list);
		}
		else if (list[i] == list[pos])
		{
			if (ft_small_char(list, pos, i) != pos)
				continue ;
			tmp = list[i];
			list[i] = list[pos];
			list[pos] = tmp;	
			return (free(tmp), list);
		}
	}
	return (list);
}

char **ft_sort_lst_exp(char **list, int i, int j, int pos)
{
	while (list[++i])
	{
		pos = 0;
		j = 0;
		while (list[++j])
		{
			if (list[j][0] < list[i][0])
			{
				pos = j;
				break ;
			}
			else if (list[j][0] == list[i][0])
				pos = ft_small_char(list, i, j , 0);
			if (pos != 0)
			{
				list = ft_swap(list, pos, -1);
				break ;
			}
		}
		if (sorted(list) == 0)
			break ;
	}
	return (list);
}

int	ft_count_list_elems(t_node lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

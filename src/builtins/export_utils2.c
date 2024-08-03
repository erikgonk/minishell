/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:08:45 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/03 13:46:35 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static char	**ft_swap(char **lst, int pos, int i)
{
	char	*tmp;

	while (lst[++i])
	{
		if (lst[i] > lst[pos])
		{
			tmp = lst[i];
			lst[i] = lst[pos];
			lst[pos] = tmp;
			return (free(tmp), lst);
		}
		else if (lst[i] == lst[pos])
		{
			if (ft_small_char(lst, pos, i, 0) != pos)
				continue ;
			tmp = lst[i];
			lst[i] = lst[pos];
			lst[pos] = tmp;
			return (free(tmp), lst);
		}
	}
	return (lst);
}

static int	ft_sorted(char **lst)
{
	int		i;
	int		j;

	i = -1;
	while (lst[++i])
	{
		j = 0;
		while (lst[i][j] == lst[i + 1][j])
			j++;
		if (lst[i][j] > lst[i + 1][j])
			return (1);
	}
	return (0);
}

char	**ft_sort_list_exp(char **lst, int i, int j, int pos)
{
	while (lst[++i])
	{
		pos = 0;
		j = 0;
		while (lst[++j])
		{
			if (lst[j][0] < lst[i][0])
			{
				pos = j;
				break ;
			}
			else if (lst[j][0] == lst[i][0])
				break ;
			pos = ft_small_char(lst, i, j, 0);
			if (pos != 0)
			{
				lst = ft_swap(lst, pos, -1);
			}
		}
		if (ft_sorted(lst) == 0)
			break ;
	}
	return (lst);
}

int	ft_count_list_elems(t_node *lst)
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

int	ft_find_char(char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

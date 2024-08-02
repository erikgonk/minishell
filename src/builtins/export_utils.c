/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:44:20 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 16:37:22 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static int	ft_lstlen(t_node *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	ft_small_char(char **list, int i, int j, int k)
{
	while (list[j][k] && list[i][k])
	{
		if (list[j][k] < list[i][k])
			return (j);
		k++;	
	}
	return (i);
}

static char	**ft_save_lst(t_node *env, char **list, int i)
{
	while (env && env->var)
	{
		list[++i] = ft_strdup(env->var);
		if (env->str)
		{
			ft_strjoin(list[i], "=");
			ft_strjoin(list[i], "\"");
			ft_strjoin(list[i], env->str);
			ft_strjoin(list[i], "\"");
		}
		else
		{
			ft_strjoin(list[i], "=");
			ft_strjoin(list[i], "\"\"");
		}
	}
	list = ft_sort_lst_exp(list, -1, 0, 0);
	return (list);
}

static void	ft_printing(char **list)
{
	int		i;

	i = -1;
	while (list[++i])
		ft_printf("%s\n", list[i], 1);
}

int	ft_print_export(t_exec *exec)
{
	int			i;
	char		**lst;

	i = -1;
	lst = malloc(sizeof (char *) * ft_count_list_elems(exec->env_t->start));
	if (!lst)
		return (1);
	lst = ft_save_lst(exec->env_t->start, lst, -1);
	ft_printing(lst);
	ft_free_willy(lst);
	return (0);
}

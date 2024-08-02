/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:44:20 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 10:53:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_small_char(char **list, int i, int j, int k)
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
		if (env.str)
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

void	ft_print_export(t_exec *exec)
{
	char		**list = NULL;
	int			i;

	list = malloc(sizeof (char *) * ft_count_ist_elems(exec->env_t->start) + 1);
	i = -1;
	list = ft_save_lst(exec->env_t->start, list, -1);
	ft_printing(list);
	while (list[++i])
		free(list[i]);
	free(list);
}

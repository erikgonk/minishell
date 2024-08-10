/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:44:20 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 18:48:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

/*
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
*/

int	ft_small_char(char **lst, int i, int j, int k)
{
	while (lst[j][k] && lst[i][k])
	{
		if (lst[j][k] < lst[i][k])
			return (j);
		k++;
	}
	return (i);
}

static char	**ft_save_lst(t_node *env, char **lst, int i)
{
	while (env && env->var)
	{
		lst[++i] = ft_strdup(env->var);
		if (env->str)
		{
			ft_strjoin(lst[i], "=");
			ft_strjoin(lst[i], "\"");
			ft_strjoin(lst[i], env->str);
			ft_strjoin(lst[i], "\"");
		}
		else
		{
			ft_strjoin(lst[i], "=");
			ft_strjoin(lst[i], "\"\"");
		}
	}
	lst = ft_sort_lst_exp(lst, -1, 0, 0);
	return (lst);
}

static void	ft_printing(char **lst)
{
	int		i;

	i = -1;
	while (lst[++i])
	{
		ft_printf(1, "declare -x ");
		ft_printf(1, "%s\n", lst[i]);
	}
}

int	ft_print_export(t_exec *exec)
{
	char		**lst;

	lst = malloc(sizeof (char *) * ft_count_lst_elems(exec->env_t->start));
	if (!lst)
		return (1);
	lst = ft_save_lst(exec->env_t->start, lst, -1);
	ft_printing(lst);
	ft_free_willy(lst);
	return (0);
}

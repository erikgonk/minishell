/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:44:20 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 12:45:55 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

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
	char		*tmp;

	if (!env || env->var)
		return (NULL);
	while (env && env->var)
	{
		lst[++i] = ft_strdup(env->var);
		tmp = ft_strjoin(lst[i], "=");
		free(lst[i]);
		lst[i] = tmp;
		lst[i] = ft_strjoin(tmp, "\"");
		free(tmp);
		tmp = lst[i];
		if (env->str)
		{
			tmp = ft_strjoin(lst[i], env->str);
			free(lst[i]);
			lst[i] = tmp;
			lst[i] = ft_strjoin(tmp, "\"");
		}
		else
			lst[i] = ft_strjoin(tmp, "\"");
		free(tmp);
		env = env->next;
	}
	lst[i] = NULL;
	lst = ft_sort_lst_exp(lst, -1, 0, 0);
	return (lst);
}

static void	ft_printing(char **lst)
{
	int		i;

	i = -1;
	while (lst && lst[++i])
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
	if (lst)
		ft_free_willy(lst);
	return (0);
}

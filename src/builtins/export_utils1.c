/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:44:20 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 20:00:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

int	ft_parsing(char *str)
{
	int		i;
	char	**cmd;

	i = -1;
	cmd = ft_split(str, '=');
	if (!cmd)
		return (1);
	while (cmd[0][++i])
	{
		if (!ft_isalpha(cmd[0][i]) && cmd[0][i] != '_' && cmd[0][i] != '=')
		{
			if (cmd[0][i] == '+' && cmd[0][i + 1] == '=')
			{
				i++;
				continue ;
			}
			ft_printf(2, "bash: export: ");
			ft_printf(2, "`%s': not a valid identifier\n", str);
			ft_free_willy(cmd);
			return (1);
		}
	}
	ft_free_willy(cmd);
	return (0);
}

int	ft_count_lst_elems(t_node *lst)
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
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

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

int	ft_print_export(t_node *node)
{
	while (node)
	{
		ft_printf(1, "declare -x ");
		if (node->var)
		{ ft_printf(1, "%s", node->var);
			if (node->str)
				ft_printf(1, "=\"%s\"", node->str);
			printf("\n");
		}
		node = node->next;
	}
	return (0);
}

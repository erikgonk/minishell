/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:43:16 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/22 13:25:06 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/minishell.h"

t_node	*get_env_lst(char *to_find, t_node *lst)
{
	int		i;
	int		j;

	i = ft_strlen(to_find);
	j = ft_strlen(lst->var);
	if (i != j)
		return (NULL);
	while (lst)
	{
		if (ft_strncmp(to_find, lst->var, i) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_print_env(t_node env)
{
	while (env)
	{
		if (env->var && env->str)
			ft_printf("%s=%s", env->var, env->str, 1);
		env = env->next;
	}
}

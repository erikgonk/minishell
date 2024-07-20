/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:43:16 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/20 19:37:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/minishell.h"

t_node	*get_env_lst(char *to_find, t_env *aux)
{
	while (aux)
	{
		if (ft_strncmp(to_find, aux->start.var, 3) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

void	ft_print_env(t_node env)
{
	while (env)
	{
		if (env.var && env.str)
			ft_printf("%s=%s", env.var, env.str, 1);
		env = env.next;
	}
}

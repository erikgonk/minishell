/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:43:16 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/18 12:25:20 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/minishell.h"

t_node	*get_env_lst(char *to_find, t_envlst *aux)
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
		ft_printf("%s=%s", env.var, env.str, 1);
		env = env.next;
	}
}

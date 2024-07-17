/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:43:16 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/17 14:45:18 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/minishell.h"

char	*get_env(char *to_find, t_data cmd)
{
	t_node *aux;

	aux = cmd.env.start;
	while (aux)
	{
		if (ft_strncmp(to_find, aux->value, 3) == 0)
			return (aux->value);
		aux = aux->next;
	}
	return (NULL);
}

void	ft_print_env(t_env env)
{
	while (env)
	{
		ft_printf("%s=%s", env.name, env.value, 1);
		env = env.next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:44:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/07 14:44:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

char	**ft_free_willy(char **split)
{
	int		i;

	i = -1;
	if (!split)
		return (NULL);
	while (split[++i])
		free(split[i]);
	free(split);
	return (0);
}


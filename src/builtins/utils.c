/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:19:54 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/21 12:23:05 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static char	**ft_free_willy(char **split)
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

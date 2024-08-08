/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:44:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 11:53:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

char	**ft_free_willy(char **cmd)
{
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	return (0);
}


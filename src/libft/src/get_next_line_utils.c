/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:53:14 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/17 14:34:00 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_free(char *buffer, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	if (!tmp)
	{
		free(line);
		free(buffer);
		return (line = NULL, buffer = NULL, NULL);
	}
	free(line);
	free(buffer);
	return (line = NULL, buffer = NULL, tmp);
}

int	checker(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\0' || buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

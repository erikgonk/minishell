/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/01/14 06:15:32 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		if (!s2[i])
			return (-1);
		i++;
	}
	while (s1[j] == s2[j] && s2[j])
	{
		if (!s1[j])
			return (-1);
		j++;
	}
	return (i - j);
}

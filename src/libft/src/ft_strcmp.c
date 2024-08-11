/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/11 13:35:00 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (-1);
	if (!s1 && s2)
		return (-1);
	else if (s1 && !s2)
		return (-1);
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
		if (!s2[i])
			return (-1);
	}
	while (s2[j] && s1[j] == s2[j])
	{
		j++;
		if (!s1[j])
			return (-1);
	}
	return (i - j);
}

int	ft_strcmp_bi(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

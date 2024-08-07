/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:09:26 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/10 16:13:33 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char		*c;
	char		*c_s1;
	size_t		i;

	c_s1 = (char *)s1;
	c = (char *)malloc(ft_strlen(c_s1) + 1);
	if (!c)
		return (0);
	i = 0;
	while (c_s1[i] != '\0')
	{
		c[i] = c_s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

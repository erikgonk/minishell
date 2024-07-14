/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:00 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/10 16:14:05 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && dstsize - 1 > i)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argv
	printf ("%zu\n", ft_strlcpy(a,"", 3));
//	printf("%s\n", a);
//	strlcpy(a, "", 3);
//	printf("%s\n", a);
//	ft_putnbr(i);
	return 0;
}*/

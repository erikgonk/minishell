/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:33 by erigonza          #+#    #+#             */
/*   Updated: 2024/01/13 21:13:39 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && !needle)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && len > 0)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len > i + j && haystack[i + j]
			&& needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	char	*str = strnstr(argv[1], argv[2], atoi(argv[3]));
	printf("%s", str);
	return (0);
}*/

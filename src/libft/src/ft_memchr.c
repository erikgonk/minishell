/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:18:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/01/12 13:06:41 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;

	str = s;
	while (n > 0)
	{
		if (*str == (unsigned char)c)
			return ((unsigned char *)str);
		str++;
		n--;
	}
	return (NULL);
}

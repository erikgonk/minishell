/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:09:34 by erigonza          #+#    #+#             */
/*   Updated: 2024/01/20 15:59:15 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*((unsigned char *)s++) = 0;
}
/*
void	ft_bzero(void *s, size_t n)
{
	size_t		i;

	if (n == 0)
		return ;
	i = 0;
	while (n--)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}*/

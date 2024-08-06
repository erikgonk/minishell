/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 00:48:49 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/10 16:16:04 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/*
char example(unsigned int a, char b)
{
	return a + b;
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	char		*str;
	int			len;

	i = 0;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

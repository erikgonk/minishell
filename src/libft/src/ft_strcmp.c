/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:43:54 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/17 11:43:57 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

 int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

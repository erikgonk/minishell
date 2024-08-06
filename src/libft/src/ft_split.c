/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:05:38 by erigonza          #+#    #+#             */
/*   Updated: 2024/04/14 15:03:16 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	**free_willy(char **split, int j)
{
	while (j >= 0)
		free(split[j--]);
	free(split);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;
	int		start;

	start = 0;
	split = malloc(sizeof (char *) * (count_words(s, c) + 1));
	if (!split)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			split[j++] = ft_substr(s, start, i - start + 1);
			if (split[j - 1] == 0)
				return (free_willy(split, j - 2));
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

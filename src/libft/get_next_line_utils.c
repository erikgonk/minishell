/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:53:14 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/17 14:34:00 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_calloc(int count, int size)
// {
// 	void		*puntero;
// 	char		*ch;
// 	int			i;

// 	puntero = malloc((count * size) * sizeof (char));
// 	if (!puntero)
// 		return (NULL);
// 	ch = puntero;
// 	i = 0;
// 	while (i < (count * size))
// 	{
// 		ch[i] = '\0';
// 		i++;
// 	}
// 	return (puntero);
// }

// int	ft_strlen(const char *s)
// {
// 	unsigned int	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t		i;
// 	size_t		j;
// 	char		*str;

// 	i = 0;
// 	j = 0;
// 	if (!(s1 && s2))
// 		return (NULL);
// 	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		str[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

char	*ft_free(char *buffer, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	if (!tmp)
	{
		free(line);
		free(buffer);
		return (line = NULL, buffer = NULL, NULL);
	}
	free(line);
	free(buffer);
	return (line = NULL, buffer = NULL, tmp);
}

int	checker(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\0' || buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

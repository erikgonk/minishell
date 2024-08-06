/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:55:28 by erigonza          #+#    #+#             */
/*   Updated: 2024/03/17 14:33:50 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*next_line(char *buffer, int i, int s_tmp)
{
	char		*tmp;
	int			len;

	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	tmp = ft_calloc((len - i + 1), 1);
	while (buffer[i])
		tmp[s_tmp++] = buffer[i++];
	return (free(buffer), buffer = NULL, tmp);
}

static char	*line(char *buffer, int i, int mall)
{
	char	*tmp;

	while (buffer[mall] && buffer[mall] != '\n')
		mall++;
	mall += (buffer[mall] == '\n');
	tmp = ft_calloc((mall + 1), 1);
	while (buffer[i] && buffer[i] != '\n')
	{
		tmp[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		tmp[i] = '\n';
	return (tmp);
}

static char	*while_reading(char *buffer, char *line, int fd)
{
	char	*tmp;
	int		byte_count;

	byte_count = 1;
	while (byte_count > 0)
	{
		buffer = ft_calloc((1 + 1), 1);
		if (!buffer)
			return (free(line), line = NULL, NULL);
		byte_count = read(fd, buffer, 1);
		if (byte_count < 0)
			return (free(line), line = NULL, free(buffer), buffer = NULL, NULL);
		if (byte_count == 0)
			return (ft_free(buffer, NULL), line);
		if (checker(buffer) == 0 || checker(line) == 0)
		{
			tmp = line;
			line = ft_strjoin(line, buffer);
			return (free(tmp), tmp = NULL, free(buffer), buffer = NULL, line);
		}
		else
			line = ft_free(buffer, line);
	}
	return (line);
}

static char	*reading(int fd, char *buffer)
{
	char		*line;

	if (!buffer)
	{
		line = ft_calloc(1, 1);
		if (!line)
			return (NULL);
	}
	else
		line = buffer;
	line = while_reading(buffer, line, fd);
	if (!line)
		return (free(line), line = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*res;

	if (fd < 0)
		return (NULL);
	buffer = reading(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	res = line(buffer, 0, 0);
	if (!res || (res[0] == '\0'))
	{
		if (buffer)
			free(buffer);
		return (buffer = NULL, res);
	}
	buffer = next_line(buffer, 0, 0);
	if (!buffer)
		return (free(res), res = NULL, NULL);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:10:08 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 19:15:24 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	putstr(int fd, char *str, int *len)
{
	int		i;

	i = 0;
	if (!str)
	{
		*len += write(fd, "(null)", 6);
		return ;
	}
	while (str[i])
	{
		if (ft_putchar_fd(fd, str[i]) == -1)
		{
			*len = -1;
			return ;
		}
		(*len)++;
		i++;
	}
}

static void	unsign(unsigned long n, int *len, unsigned int base, int type)
{
	char	*c;

	if (*len == -1)
		return ;
	c = "0123456789abcdef";
	if (type == 88)
		c = "0123456789ABCDEF";
	if (type == 112)
		putstr(1, "0x", len);
	if (n >= base && *len != -1)
	{
		unsign(n / base, len, base, type);
		if (*len == -1)
			return ;
	}
	if (ft_putchar_fd(1, c[n % base]) == -1)
	{
		*len = -1;
		return ;
	}
	else
		(*len)++;
}

static void	putnb(long long int n, int base, char *c, int *len)
{
	if (base == 10 && (n > 2147483647 || n < -2147483648))
		return ;
	if (n < 0)
	{
		putstr(1, "-", len);
		if (*len == -1)
			return ;
		n = -n;
	}
	if (n >= base && *len != -1)
	{
		putnb(n / base, base, c, len);
		if (*len == -1)
			return ;
	}
	if ((*len)++ != -1 && ft_putchar_fd(1, c[n % base]) == -1)
	{
		*len = -1;
		return ;
	}
}

static int	printea(int fd, const char str, int len, va_list args)
{
	char	*c;

	c = "0123456789abcdef";
	if (len == -1)
		return (-1);
	else if (str == 's')
		putstr(fd, va_arg(args, char *), &len);
	else if (str == 'c')
		len += ft_putchar_fd(1, va_arg(args, int));
	else if (str == 'd' || str == 'i')
		putnb(va_arg(args, int), 10, c, &len);
	else if (str == 'u')
		unsign(va_arg(args, unsigned int), &len, 10, 0);
	else if (str == 'x' || str == 'X')
		unsign(va_arg(args, unsigned int), &len, 16, str);
	else if (str == 'p')
		unsign(va_arg(args, unsigned long), &len, 16, 112);
	else if (str == '%')
		len += ft_putchar_fd(1, '%');
	return (len);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		count;
	va_list	args;
	int		j;
	int		error;

	count = 0;
	va_start(args, str);
	j = 0;
	while (str[j])
	{
		if (str[j] == '%')
			error = printea(fd, str[++j], 0, args);
		else
			error = ft_putchar_fd(1, str[j]);
		if (error == -1)
		{
			va_end(args);
			return (-1);
		}
		count += error;
		if (str[j])
			++j;
	}
	va_end(args);
	return (count);
}

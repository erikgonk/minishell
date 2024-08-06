/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:10:08 by erigonza          #+#    #+#             */
/*   Updated: 2024/05/24 18:39:41 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	putstr(int fd, char *str, t_libft *l)
{
	int		i;

	i = 0;
	if (!str)
	{
		l->len += write(fd, "(null)", 6);
		return ;
	}
	while (str[i])
	{
		if (ft_putchar_fd(fd, str[i]) == -1)
		{
			l->len = -1;
			return ;
		}
		l->len++;
		i++;
	}
}

static void	unsign(unsigned long n, t_libft *l, unsigned int base, int type)
{
	if (l->len == -1)
		return ;
	if (type == 88)
		l->c = "0123456789ABCDEF";
	if (type == 112)
		putstr(1, "0x", l);
	if (n >= base && l->len != -1)
	{
		unsign(n / base, l, base, type);
		if (l->len == -1)
			return ;
	}
	if (ft_putchar_fd(l->fd, l->c[n % base]) == -1)
	{
		l->len = -1;
		return ;
	}
	else
		l->len++;
}

static void	putnb(long long int n, int base, t_libft *l)
{
	if (base == 10 && (n > 2147483647 || n < -2147483648))
		return ;
	if (n < 0)
	{
		putstr(l->fd, "-", l);
		if (l->len == -1)
			return ;
		n = -n;
	}
	if (n >= base && l->len != -1)
	{
		putnb(n / base, base, l);
		if (l->len == -1)
			return ;
	}
	if (l->len++ != -1 && ft_putchar_fd(l->fd, l->c[n % base]) == -1)
	{
		l->len = -1;
		return ;
	}
}

static int	printea(t_libft *l, const char str, va_list args)
{
	l->c = "0123456789abcdef";
	l->len = 0;
	if (l->len == -1)
		return (-1);
	else if (str == 's')
		putstr(l->fd, va_arg(args, char *), l);
	else if (str == 'c')
		l->len += ft_putchar_fd(l->fd, va_arg(args, int));
	else if (str == 'd' || str == 'i')
		putnb(va_arg(args, int), 10, l);
	else if (str == 'u')
		unsign(va_arg(args, unsigned int), l, 10, 0);
	else if (str == 'x' || str == 'X')
		unsign(va_arg(args, unsigned int), l, 16, str);
	else if (str == 'p')
		unsign(va_arg(args, unsigned long), l, 16, 112);
	else if (str == '%')
		l->len += write(l->fd, "%", 1);
	return (l->len);
}

int	fd_printf(int fd, const char *str, ...)
{
	int					count;
	t_libft				l;
	va_list				args;

	l.fd = fd;
	count = 0;
	va_start(args, str);
	l.i = 0;
	while (str[l.i])
	{
		if (str[l.i] == '%')
			l.error = printea(&l, str[++l.i], args);
		else
			l.error = ft_putchar_fd(l.fd, str[l.i]);
		if (l.error == -1)
		{
			va_end(args);
			return (-1);
		}
		count += l.error;
		if (str[l.i])
			++l.i;
	}
	va_end(args);
	return (count);
}

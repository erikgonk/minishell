/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:18:45 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/03 15:57:02 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

long long int	ft_atoll(char *str, int i, long long int res, int sign)
{
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		printf("%lld\n", res);
		if (res < 0)
			return (1);
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (res < 0)
		return (1);
	res *= sign;
	return (res);
}

static void	ft_check_is_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf("exit\n", 2);
			ft_printf("minish: exit: ", 2);
			ft_printf("%s: numeric argument required\n", str, 2);
			exit (2);
		}
	}
}

int	ft_exit(t_exec *exec)
{
	t_data			*data;
	long long int	res;

	if (!exec->cmd_t->cmd[1])
		exit (data->g_exit);
	ft_check_is_num(exec->cmd_t->cmd[1]);
	if (exec->cmd_t->cmd[2])
	{
		ft_printf("exit\nminish: exit: too many arguments\n", 2);
		exit (1);
	}
	res = ft_atoll(exec->cmd_t->cmd[1], 0, 0, 1);
	if (res == 1 && exec->cmd_t->cmd[1][1])
	{
		ft_printf("exit\n", 2);
		ft_printf("minish: exit: ", 2);
		ft_printf("%s: ", exec->cmd_t->cmd[1], 2);
		ft_printf("numeric argument required\n", 2);
		exit (2);
	}
	exit (res);
}

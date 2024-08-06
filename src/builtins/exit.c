/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:18:45 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 16:07:41 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"
#include "../../inc/exec.h"

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
		ft_printf(1, "%lld\n", res);
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

static void	ft_exit_status(int	err)
{
	ft_get_stt(1, err);
	exit (err);
}

static void	ft_check_is_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf(2, "exit\n");
			ft_printf(2, "minish: exit: ");
			ft_printf(2, "%s: numeric argument required\n", str);
			ft_exit_status(2);
		}
	}
}

int	ft_exit(t_exec *exec)
{
	long long int	res;

	res = 0;
	if (!exec->cmd_t->cmd[1])
		ft_exit_status(0);
	ft_check_is_num(exec->cmd_t->cmd[1]);
	if (exec->cmd_t->cmd[2])
	{
		ft_printf(2, "exit\nminish: exit: too many arguments\n");
		ft_exit_status(res);
	}
	res = ft_atoll(exec->cmd_t->cmd[1], 0, 0, 1);
	if (res == 1 && exec->cmd_t->cmd[1][1])
	{
		ft_printf(2, "exit\n");
		ft_printf(2, "minish: exit: ");
		ft_printf(2, "%s: ", exec->cmd_t->cmd[1]);
		ft_printf(2, "numeric argument required\n");
		exit (2);
	}
	ft_exit_status(res);
	return (0);
}

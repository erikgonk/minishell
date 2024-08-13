/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:18:45 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 17:50:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"

long long int   ft_atoll(char *str, int i, long long int res, int sign)
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
			if (res < 0)
					return (1);
			res = (res * 10) + (str[i] - 48);
			i++;
	}
	if (res < 0)
			return (-1);
	res *= sign;
	return (res);
}

static void     ft_exit_status(int err)
{
	ft_printf(1, "exit\n");
	exit (err);
}

static void     ft_print_err(char *str)
{
	ft_printf(2, "minish: exit: ");
	ft_printf(2, "%s: numeric argument required\n", str);
	ft_exit_status(2);
}

static void     ft_check_is_num(char *str)
{
	int             i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (!str[++i + 1])
			ft_print_err(str);
	}
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			ft_print_err(str);
	}
}

int     ft_exit(t_exec *exec)
{
    long long int   res;
	
	if (!exec->cmd_t->cmd[1])
		ft_exit_status(exec->g_exit);
	ft_check_is_num(exec->cmd_t->cmd[1]);
	if (exec->cmd_t->cmd[2])
	{
		ft_printf(2, "exit\nminish: exit: too many arguments\n");
		return (1);
	}
	res = ft_atoll(exec->cmd_t->cmd[1], 0, 0, 1);
	if (res == -1 && exec->cmd_t->cmd[1][1])
	{
		if (exec->cmd_t->cmd[1][0] == '-' && exec->cmd_t->cmd[1][1] == '1')
			ft_exit_status(res);
		ft_printf(2, "exit\n");
		ft_printf(2, "minish: exit: ");
		ft_printf(2, "%s: ", exec->cmd_t->cmd[1]);
		ft_printf(2, "numeric argument required\n");
		ft_exit_status(2);
	}
	ft_exit_status(res);
	return (0);
}

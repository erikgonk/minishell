/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:32:56 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 11:29:03 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static int	ft_n_checker(char *str)
{
	int		i;

	i = -1;
	if (!str || !str[++i])
		return (0);
	while (str[++i] && str[i] == 'n')
	{
		if (!str[i + 1])
			return (1);
		else if (str[i + 1] != 'n')
			return (0);
	}
	return (0);
}

static int	ft_n(char **cmd, int i, int *flag)
{
	if (cmd[i] && cmd[i][0] == '-' && ft_n_checker(cmd[i]) == 1)
		*flag = 1;
	else
		return (1);
	if (*flag == 1 && (cmd[i + 1] && ft_n_checker(cmd[i + 1]) == 0))
		return (++i);
	while (ft_n_checker(cmd[i + 1]) == 1)
		i++;
	return (++i);
}

int	ft_echo(t_exec *exec)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (!exec->cmd_t->cmd[i])
	{
		ft_printf(1, "\n");
		return (0);
	}
	i = ft_n(exec->cmd_t->cmd, i, &flag);
	while (exec->cmd_t->cmd[i])
	{
		ft_printf(1, "%s", exec->cmd_t->cmd[i++]);
		if (exec->cmd_t->cmd[i])
			ft_printf(1, " ");
	}
	if (flag == 0)
		ft_printf(1, "\n");
	return (0);
}

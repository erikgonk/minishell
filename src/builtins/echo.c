/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:32:56 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/07 12:11:38 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

void	ft_n_checker(char **cmd, int i, int *flag)
{
	int		j;

	j = 0;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][++j] == 'n')
	{
		*flag = 1;
		if (!cmd[i][j + 1])
		{
			j = 0;
			i++;
		}
		else if (cmd[1][j + 1] != 'n')
		{
			*flag = 0;
			return ;
		}
	}
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
	ft_n_checker(exec->cmd_t->cmd, i, &flag);
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

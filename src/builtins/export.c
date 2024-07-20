/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/18 14:45:57 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static int	ft_parsing(char *str, int flag)
{
	if (!ft_isalpha(*str) && *str != '_' && *str != '=')
		return (1);
}

static add_create
static void	create_env(char *flag, t_data cmd, char add)
{
	if ()
}

int	ft_export(t_data cmd, int i)
{
	int		j;
	char	*var;
	char	*str;

	j = -1;
	var = malloc(1);
	str = malloc(1);
	if (cmd->cmd[i][0] == '=')
	{
		ft_printf("mish: export: `=': not a valid identifier");
		return (1);
	}
	while (cmd.cmd[i + 1][++j])
	{
		if (ft_parsing(cmd.cmd[i], 0) == 1)
			return (1);
	}
}

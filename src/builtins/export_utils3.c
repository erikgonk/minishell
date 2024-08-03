/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:44:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/03 13:45:00 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

int	ft_parsing(char *str)
{
	int		i;
	char	**cmd;

	i = -1;
	cmd = ft_split(str, '=');
	if (!cmd)
		return (1);
	while (cmd[0][++i])
	{
		if (!ft_isalpha(cmd[0][i]) && cmd[0][i] != '_' && cmd[0][i] != '=')
		{
			if (cmd[0][i] == '+' && cmd[0][i + 1] == '=')
			{
				i++;
				continue ;
			}
			ft_printf("bash: export: ", 2);
			ft_printf("`%s': not a valid identifier\n", str, 2);
			ft_free_willy(cmd);
			return (1);
		}
	}
	ft_free_willy(cmd);
	return (0);
}

/2e9f042cbecf8af0c3400cf69b7b34230398ee3i* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:44:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 15:32:43 by erigonza         ###   ########.fr       */
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
			ft_printf(2, "bash: export: ");
			ft_printf(2, "`%s': not a valid identifier\n", str);
			ft_free_willy(cmd);
			return (1);
		}
	}
	ft_free_willy(cmd);
	return (0);
}

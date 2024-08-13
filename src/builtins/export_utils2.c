/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:44:23 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/13 18:23:09 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

int	ft_parsing_normi(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=' || i == 0)
			{
				ft_printf(2, "bash: export: ");
				ft_printf(2, "`%s': not a valid identifier\n", str);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_export_flag(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i + 1] && str[i + 2] && str[i] == '+' && str[i + 1] == '=')
			return (ADD);
		if (str[i] == '=')
			return (TRUNC);
	}
	return (TRUNC);
}

char	*ft_export_get_var(char *str, int flag)
{
	char	*tmp;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (flag == ADD && str[i] == '+')
		{
			tmp = ft_substr(str, 0, i);
			return (tmp);
		}
		else if (flag == TRUNC && str[i] == '=')
		{
			tmp = ft_substr(str, 0, i);
			return (tmp);
		}
	}
	tmp = ft_strdup(str);
	return (tmp);
}

char	*ft_export_get_str(t_exec *exec, char *cmd, int flag)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			if (!cmd[i + 1])
			{
				if (flag == 1)
					exec->flag_b = -1;
				return (ft_strdup(""));
			}
			tmp = ft_substr(cmd, (i + 1), (ft_strlen(cmd) - i - 1));
			return (tmp);
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/20 18:44:14 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

static int	ft_parsing(char *str)
{
	i = -1;
	while (str[++i])
	{
		else if (!ft_isalpha(*str) && *str != '_' && *str != '=')
			return (2);
		else
			return (0);
		return (1);
	}
}

static void	ft_env_exists(t_env *env, char *str, int i, int flag)
{
	char	*tmp = NULL;

	while (env)
	{
		while (env.var[++i] && str[i] && env.str[i])
		{
			*tmp = ft_strchr
			if (env.var[i] != str[i])
			{
				return ;
			}
			if (env.str[i + 1] != str[i])
			{
				ft_create_env(env, str, flag);
				return ;
			}
		}
		if (flag2 == 2)
			ft_create_env(env, str, flag);
	}
}

static void	ft_create_env(t_env env, char *str, int flag)
{
	int			i;
	char	**cmd = NULL;

	i = -1;
	if (flag == F_ADD)
		cmd = ft_split(str, "+");
	else if (flag == F_CREATE)
		cmd = ft_split(str, "=");
	while (cmd[++i])
	{
		
	}



	if (ft_parsing(cmd->cmd[i]) != 0)
			return (1);
}

int	ft_export(t_data *cmd, int i)
{
	char	*tmp = NULL;

	if (!cmd->cmd[i + 1])
		ft_print_export(cmd);
	while (cmd->cmd[++i])
	{
		*tmp = ft_strchr(cmd->cmd[i], '+');
		if (cmd->cmd[i] == '=')
		{
			ft_pritf("mish: export: `%s': not a valid identifier\n", str, 0);
			return (1);
		}
		if (*tmp + 1 == '=')
			ft_create_env(cmd->env, cmd->cmd[i], F_ADD)
		else if (!ft_strchr(cmd->cmd[i], '='))
			ft_create_env(cmd->env, cmd->cmd[i], F_NONE);
		else
			ft_create_env(cmd->env, cmd->cmd[i], F_CREATE)
	}
	return (free(tmp), 0);
}
// DONE export --> show env
// export Hola --> save hola in env but with no str
// export Hola=HOLA --> if Hola exists -> change the str of Hola to HOLA || if Hola does not exist -> save Hola in var and HOLA in str
// export Hola+=aloha --> if Hola exists -> add aloha to Hola || if Hola does not exist -> do Hola=aloha

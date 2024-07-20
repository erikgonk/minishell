/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/20 19:45:15 by erigonza         ###   ########.fr       */
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
		{
			ft_printf("bash: export: `%s': not a valid identifier\n", str)
			return (1);
		}
	}
	return (0);
}

static void	ft_add_to_env(char **cmd, t_env env)
{
	t_node	*node = NULL;
	if (get_env_lst(cmd[i], env) != NULL)
	{
		node = get_env_lst(cmd[i], env);
		while (node->)
	}
}
static int	ft_create_env(t_env env, char *str, int flag)
{
	char	**cmd = NULL;
	char	*tmp = NULL;

	if (flag == F_ADD)
		cmd = ft_split(str, "+");
	else if (flag == F_CREATE)
		cmd = ft_split(str, "=");
	if (ft_parsing(cmd[0]) == 1)
		return (1);
	if (ft_strlen(cmd[0]) == )
		// meter aqui prueba si el env y la variable son del mismo tamano y si son iguales
	if (flag == F_ADD)
		ft_add_to_env(cmd, env);
	else if (flag == F_CREATE)
	{
	}
	return (0);
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

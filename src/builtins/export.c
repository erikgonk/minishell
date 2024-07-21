/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/21 14:53:58 by erigonza         ###   ########.fr       */
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

static void	ft_add_replace_str_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var=) exist
{
	t_node	*node = NULL;
	char	*tmp = NULL;

	*tmp = ft_strchr(cmd->cmds.cmd[i], '=');
	if (!*tmp + 1)// var=
		node->str = "";
	else if (flag == F_CREATE)// var=str
		node->str = cmd[1];
	else if (flag == F_ADD)// var+=str
		ft_strlcat(node->str, cmd[1], ft_strlen(cmdp1[1]));
	free(tmp);
}

static void	ft_create_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var && var=) Not exist
{
	if (cmd)// var=str && var+=str
	{
		node->var = cmd[0];
		node->str = cmd[1]; 
		return ;
	}
	char	*tmp;

	*tmp = ft_strchr(cmd->cmds.cmd[i], '=');
	// var
	if (!*tmp + 1 && tmp)
	{
		node->var = str;
		node->str = NULL; 
		return ;
	}
	// var=
	node->var = str;
	node->str = ""; 	
	free(tmp);
}

static int	ft_separate_export(t_env *env, char **cmd, char *str, int flag)
{
	int		err;

	err = 0;
	if (flag == F_NONE && !get_env_lst(str, env))// var NOT exist
		err = ft_create_env(env, NULL, str, flag);
	else if (flag == F_NONE)// var exist
		return (0);
	else if (flag != F_NONE && !get_env_lst(cmd[0], env))// (var=str && var+=str && var=) Not exist
		err = ft_create_env(env, cmd, str, flag);
	else// (var=str && var+=str && var=) exist
		err = ft_add_replace_str_env(env, cmd, str, flag);
	if (cmd)
		ft_free_willy(cmd);
	return (err);
}

int	ft_export(t_data *cmd, int i)
{
	char	**cmd = NULL;
	char	*tmp = NULL;
	int		err;

	err = 0;
	if (!cmd->cmds.cmd[i + 1])
		ft_print_export(cmd);
	while (cmd->cmds.cmd[++i])
	{
		*tmp = ft_strchr(cmd->cmds.cmd[i], '+');
		if (cmd->cmds.cmd[i][0] == '=')
		{
			ft_pritf("mish: export: `%s': not a valid identifier\n", cmd->cmds.cmd[i], 0);
			return (1);
		}
		if (*tmp + 1 == '=')// var+=str & var+=
			err = ft_separate_export(cmd->env, ft_split(str, "+"), cmd->cmds.cmd[i], F_ADD)
		else if (!ft_strchr(cmd->cmds.cmd[i], '='))// var
			err = ft_separate_export(cmd->env, NULL, cmd->cmds.cmd[i], F_NONE);
		else
			err = ft_separate_export(cmd->env, ft_split(str, "+"), cmd->cmds.cmd[i], F_CREATE)// var=str & var=
	}
	return (free(tmp), err);
}
// DONE export --> show env
// export Hola --> save hola in env but with no str
// export Hola=HOLA --> if Hola exists -> change the str of Hola to HOLA || if Hola does not exist -> save Hola in var and HOLA in str
// export Hola+=aloha --> if Hola exists -> add aloha to Hola || if Hola does not exist -> do Hola=aloha

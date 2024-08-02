/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 16:57:10 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static int	ft_parsing(char *str)
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
			ft_printf("bash: export: `%s': not a valid identifier\n", str, 2);
			ft_free_willy(cmd);
			return (1);
		}
	}
	ft_free_willy(cmd);
	return (0);
}

static int	ft_add_replace_str_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var=) exist
{
	t_node	*node;
	int		pos	;

	pos = ft_find_char(cmd[1], '=');
	if (!cmd[1][pos + 1])// var=
		node->str = "";
	else if (flag == F_CREATE)// var=str
		node->str = cmd[1];
	else if (flag == F_ADD)// var+=str
		ft_strlcat(node->str, cmd[1], ft_strlen(cmd[1]));
	return (0);
}

static int	ft_create_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var && var=) Not exist
{
	char		*tmp;
	t_node		*node;
	
	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	node->next = NULL;
	if (cmd)// var=str && var+=str
	{
		node->var = cmd[0];
		node->str = cmd[1]; 
		return (0);
	}
	flag =  ft_find_char(cmd[1], '=');
	env->end->next = node;
	if (flag == -1)// var
	{
		node->var = str;
		node->str = NULL; 
		return (0);
	}
	node->var = str;// var=
	node->str = ""; 	
	return (free(tmp), 1);
}

static int	ft_separate_export(t_env *env, t_exec *exec, char *str, int flag)
{
	char	**cmd;

	cmd = ft_split(exec->cmd_t->cmd[1], '+');
	if (flag == F_NONE && !get_env_lst(str, env->start))// var NOT exist
		ft_create_env(env, NULL, str, flag);
	else if (flag == F_NONE)// var exist
		return (0);
	else if (flag != F_NONE && !get_env_lst(cmd[0], env->start))// (var=str && var+=str && var=) Not exist
		ft_create_env(env, cmd, str, flag);
	else// (var=str && var+=str && var=) exist
		ft_add_replace_str_env(env, cmd, str, flag);////////////// cambiar cmd por exec??////////////////////
	if (cmd)
		ft_free_willy(cmd);
	return (exec->g_exit);
}

int	ft_export(t_exec *exec)
{
	int		i;
	int		pos;

	i = 0;
	if (!exec->cmd_t->cmd[1])
		return (ft_print_export(exec));
	while (exec->cmd_t->cmd[++i])
	{
		if (ft_parsing(exec->cmd_t->cmd[i]) == 1)
			return (1);
		pos = ft_find_char(exec->cmd_t->cmd[i], '=');
		if (exec->cmd_t->cmd[i][0] == '=')
		{
			ft_pritf("mish: export: `%s': not a valid identifier\n", exec->cmd_t->cmd[i], 2);
			return (1);
		}
		if (pos == -1)// var
			exec->g_exit = ft_separate_export(exec->env_t, exec, exec->cmd_t->cmd[i], F_NONE);
		else if (exec->cmd_t->cmd[i][pos -1] == '+')// var+=str & var+=
			exec->g_exit = ft_separate_export(exec->env_t, exec, exec->cmd_t->cmd[i], F_ADD);
		else
			exec->g_exit = ft_separate_export(exec->env_t, exec, exec->cmd_t->cmd[i], F_CREATE);// var=str & var
	}
	return (exec->g_exit);
}
// DONE export --> show env
// export Hola --> save hola in env but with no str
// export Hola=HOLA --> if Hola exists -> change the str of Hola to HOLA || if Hola does not exist -> save Hola in var and HOLA in str
// export Hola+=aloha --> if Hola exists -> add aloha to Hola || if Hola does not exist -> do Hola=aloha

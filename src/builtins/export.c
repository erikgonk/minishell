/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 10:53:27 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"
#include "../../inc/exec.h"


static int	ft_parsing(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
		{
			if (str[i] == '+' && str[i + 1] == '=')
			{
				i++;
				continue ;
			}
			ft_printf("bash: export: `%s': not a valid identifier\n", str, 2);
			return (1);
		}
	}
	return (0);
}

static void	ft_add_replace_str_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var=) exist
{
	t_node	*node = NULL;
	char	*tmp = NULL;

	*tmp = ft_strchr(cmd[1], '=');
	if (!*tmp + 1)// var=
		node->str = "";
	else if (flag == F_CREATE)// var=str
		node->str = cmd[1];
	else if (flag == F_ADD)// var+=str
		ft_strlcat(node->str, cmd[1], ft_strlen(cmd[1]));
	free(tmp);
}

static void	ft_create_env(t_env *env, char **cmd, char *str, int flag)// (var=str && var+=str && var && var=) Not exist
{
	t_node		*node = NULL;
	
	node = malloc(sizeof(t_node));
	env->end->next = node;
	node->next = NULL;
	if (cmd)// var=str && var+=str
	{
		node->var = cmd[0];
		node->str = cmd[1]; 
		return ;
	}
	char	*tmp;

	*tmp = ft_strchr(cmd[1], '=');
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

static int	ft_separate_export(t_env *env, t_exec *exec, char *str, int flag)
{
	int		err;
	char	**cmd;

	err = 0;
	cmd = ft_split(exec->cmd_t->cmd[1], '+');
	if (flag == F_NONE && !get_env_lst(str, env->start))// var NOT exist
		ft_create_env(env, NULL, str, flag);
	else if (flag == F_NONE)// var exist
		return (0);
	else if (flag != F_NONE && !get_env_lst(cmd[0], env->start))// (var=str && var+=str && var=) Not exist
		ft_create_env(env, cmd, str, flag);
	else// (var=str && var+=str && var=) exist
		ft_add_replace_str_env(env, cmd, str, flag);
	if (cmd)
		ft_free_willy(cmd);
	return (err);
}

int	ft_export(t_exec *exec)
{
	char	**str = NULL;
	char	*tmp = NULL;
	int		i;

	i = 0;
	if (ft_parsing(exec->cmd_t->cmd[i]) != 1 && !exec->cmd_t->cmd[i + 1])
		ft_print_export(cmd);
	while (exec->cmd_t->cmd[++i])
	{
		if (ft_parsing(exec->cmd_t->cmd[i]) == 1)
			return (1);
		tmp = ft_strchr(exec->cmd_t->cmd[i], '+');
		if (exec->cmd_t->cmd[i][0] == '=')
		{
			ft_pritf("mish: export: `%s': not a valid identifier\n", exec->cmd_t->cmd[i], 0);
			return (free(tmp), 1);
		}
		if (*tmp + 1 == '=')// var+=str & var+=
			exec->g_exit= ft_separate_export(exec->env_t, exec, exec->cmd_t->cmd[i], F_ADD);
		else if (!ft_strchr(exec->cmds->cmd[i], '='))// var
			exec->g_exit = ft_separate_export(exec->env_t, NULL, exec->cmd_t->cmd[ia], F_NONE);
		else
			exec->g_exit = ft_separate_export(cmd->env, exec, exec->cmd_t->cmd[i], F_CREATE);// var=str & var
		free(tmp);
	}
	return (free(tmp), err);
}
// DONE export --> show env
// export Hola --> save hola in env but with no str
// export Hola=HOLA --> if Hola exists -> change the str of Hola to HOLA || if Hola does not exist -> save Hola in var and HOLA in str
// export Hola+=aloha --> if Hola exists -> add aloha to Hola || if Hola does not exist -> do Hola=aloha

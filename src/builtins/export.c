/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:13 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 19:59:54 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

static void	ft_add_one(t_exec *exec, t_node *lst, t_node *node)
{
	if (!lst)
		return ;
	while (lst && lst->next)
		lst = lst->next;
	exec->env_t->end = node;
	lst->next = node;
	node->next = NULL;
}

static int	ft_add_replace_str_env(t_exec *exec, char **cmd, int flag) // (var=str && var+=str && var=) exist
{
	t_node	*node;

	node = ft_get_env_lst(cmd[0], exec->env_t->start);
	if (!cmd[1] && flag == F_CREATE) // var= when !str
	{
		if (node->str)
			free(node->str);
		node->str = malloc(sizeof(char) + 1);
		node->str = ft_strdup("");
	}
	else if (flag == F_ADD && cmd[1])
	{
		free(node);
		node = ft_get_env_lst(ft_strtrim(cmd[0], "+"), exec->env_t->start);
		ft_strlcat(node->str, cmd[1], ft_strlen(cmd[1]));
	}
	else if (flag == F_CREATE) // var=str
	{
		if (node->str)
			free(node->str);
		node->str = ft_strdup(cmd[1]);
	}
	ft_free_willy(cmd);
	return (0);
}

// (var=str && var+=str && var && var=) Not exist
static int	ft_create_env(t_exec *exec, char **cmd, char *str, int flag)
{
	t_node		*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	ft_add_one(exec, exec->env_t->start, node);
	if (!cmd && flag == F_NONE) // var
	{
		node->var = ft_strdup(str);
		node->str = NULL;
		return (0);

	}
	if (cmd) // var=str && var+=str
	{
		node->var = ft_strdup(cmd[0]);
		node->str = ft_strdup(cmd[1]);
		return (0);
	}
	if (cmd && cmd[1])
		flag = ft_find_char(cmd[1], '=');
	node->var = ft_strdup(str); // var=
	node->str = ft_strdup("");
	return (1);
}

static int	ft_separate_export(t_env *env, t_exec *exec, char *str, int flag)
{
	char	**cmd;

	cmd = ft_split(exec->cmd_t->cmd[1], '=');
	if (!cmd)
		return (-1);
	if (cmd[0][ft_strlen(cmd[0]) - 1] == '+')
	{	
		ft_free_willy(cmd);
		cmd = ft_split(exec->cmd_t->cmd[1], '=');
		if (!cmd)
			return (-1);
	}
	if (flag == F_NONE && !ft_get_env_lst(str, env->start)) // var NOT exist
		ft_create_env(exec, NULL, str, flag);
	else if (flag == F_NONE) // var exist
		return (0);
	else if (flag != F_NONE)
	{
		if (cmd && !ft_get_env_lst(cmd[0], env->start) && cmd[1]) // (var+=str) Not exist
			ft_create_env(exec, cmd, str, flag);
	}
	printf("cmd -> %s\n", cmd[0]);
	if (cmd && flag != F_NONE && !ft_get_env_lst(cmd[0], env->start)) // (var=str && var+=str && var=) Not exist
		ft_create_env(exec, cmd, str, flag);
	else // (var=str && var+=str && var=) exist
		ft_add_replace_str_env(exec, cmd, flag);
	if (cmd)
		ft_free_willy(cmd);
	printf("%s\n", str);
	return (0);
}

static void	ft_export_normi(t_exec *exec, int i, int pos)
{
	if (pos == -1) // var
		exec->g_exit = ft_separate_export(exec->env_t, exec,
				exec->cmd_t->cmd[i], F_NONE);
	else if (exec->cmd_t->cmd[i][pos -1] == '+') // var+=str & var+=
		exec->g_exit = ft_separate_export(exec->env_t, exec,
				exec->cmd_t->cmd[i], F_ADD);
	else
		exec->g_exit = ft_separate_export(exec->env_t, exec,
				exec->cmd_t->cmd[i], F_CREATE); // var=str & var
}

int	ft_export(t_exec *exec)
{
	int		i;
	int		pos;

	i = 0;
	if (!exec->cmd_t->cmd[1])
		return (ft_print_export(exec->env_t->start));
	while (exec->cmd_t->cmd[++i])
	{
		if (ft_parsing(exec->cmd_t->cmd[i]) == 1)
			return (1);
		pos = ft_find_char(exec->cmd_t->cmd[i], '=');
		if (exec->cmd_t->cmd[i][0] == '=')
		{
			ft_printf(2, "mish: export: `%s'", exec->cmd_t->cmd[i]);
			ft_printf(2, ": not a valid identifier\n");
			return (1);
		}
		ft_export_normi(exec, i, pos);
	}
	return (exec->g_exit);
}

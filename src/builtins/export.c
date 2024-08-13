/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:45:35 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/13 18:34:42 by erigonza         ###   ########.fr       */
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

static void	ft_export_not_exist(t_exec *exec, char *var, char *cmd) // NOT EXIST
{
	t_node	*node;
	char	*str;

	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	ft_add_one(exec, exec->env_t->start, node);
	str = ft_export_get_str(exec, cmd, 1);
	node->var = ft_strdup(var);
	if (!str) // var
		node->str = NULL;
	else if (exec->flag_b == -1) // var= var+=
		node->str = ft_strdup("");
	else if (str)
		node->str = ft_strdup(str);
	free(str);
}

static void	ft_export_exist(t_exec *exec, t_node *node, char *str) // EXIST
{
	char	*tmp;

	if (exec->flag_b == TRUNC && !str) // var=
		if (node && node->str)
			free(node->str);
	if (exec->flag_b == TRUNC && str) // var=str
	{
		if (node && node->str)
			free(node->str);
		node->str = ft_strdup(str);
	}
	else if (exec->flag_b == ADD && str) // var+=str
	{
		if (node && !node->str)
			node->str = ft_strdup(str);
		else if (node && node->str)
		{
			tmp = node->str;
			node->str = ft_strjoin(node->str, str);
			free(tmp);
		}
	}
	free(str);
}

static void	ft_export_asign(t_exec *exec, char *var, char *cmd, int flag)
{
	t_node	*node;
	char	*str;

	printf("entra con -> %s\n", cmd);
	exec->flag_b = flag;
	node = ft_get_env_lst(var, exec->env_t->start);
	str = ft_export_get_str(exec, cmd, 0);
	if (!node)
		ft_export_not_exist(exec, var, cmd); // NOT EXIST
	else
		ft_export_exist(exec, node, str); // EXISTS
	free(str);
}

int	ft_export(t_exec *exec)
{
	char	*var;
	int		flag;
	int		i;

	i = 0;
	if (!exec->cmd_t->cmd[1])
		return (ft_print_export(exec->env_t->start));
	while (exec->cmd_t->cmd[++i])
	{
		if (ft_parsing(exec->cmd_t->cmd[i], -1) == 1)
			continue ;
		if (exec->cmd_t->cmd[i][0] == '=')
		{
			ft_printf(2, "mish: export: `%s'", exec->cmd_t->cmd[i]);
			ft_printf(2, ": not a valid identifier\n");
			return (1);
		}
		flag = ft_export_flag(exec->cmd_t->cmd[i]); // FLAG
		var = ft_export_get_var(exec->cmd_t->cmd[i], flag); // VAR
		ft_export_asign(exec, var, exec->cmd_t->cmd[i], flag);
		free(var);
	}
	return (exec->g_exit);
}

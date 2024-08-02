/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 10:54:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"
#include "../../inc/exec.h"

int	ft_pwd(t_exec *exec)
{
	char		*pwd;
	t_node		*aux;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		aux = get_env_lst("PWD", exec->env_t->start);
		if (aux)
		{
			ft_printf("%s\n", aux->str, 1);
			return (0);
		}
		else if (exec->env_t->pwd)
		{
			ft_printf("%s\n", exec->env_t->pwd, 1);
			return (0);
		}
		return (1);
	}
	printf("%s\n", pwd);
	return (free(pwd), 0);
}

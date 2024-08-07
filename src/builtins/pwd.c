/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/07 12:06:59 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

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
			ft_printf(1, "%s\n", aux->str);
			return (0);
		}
		else if (exec->env_t->pwd)
		{
			ft_printf(1, "%s\n", exec->env_t->pwd);
			return (0);
		}
		return (1);
	}
	printf("%s\n", pwd);
	return (free(pwd), 0);
}

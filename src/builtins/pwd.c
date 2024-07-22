/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/20 12:03:49 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

int	ft_pwd(t_data *data)
{
	char		*pwd;
	t_env		*aux;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		aux = get_env_lst("PWD", aux);
		if (aux)
		{
			ft_printf("%s\n", aux->str, 1);
			return (0);
		}
		else if (aux->pwd)
		{
			ft_printf("%s\n", aux->pwd, 1);
			return (0);
		}
		return (1);
	}
	printf("%s\n", pwd);
	return (free(pwd, 0);
}

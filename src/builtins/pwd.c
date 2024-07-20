/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/18 13:09:48 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

int	ft_pwd(t_data data)
{
	char		*pwd;
	t_envlst	*aux;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		aux = get_env_lst("PWD", aux);
		if (aux)
		{
			printf("%s\n", aux->str);
			return (0);
		}
		return (1);
	}
	printf("%s\n", pwd);
	return (free(pwd, 0);
}

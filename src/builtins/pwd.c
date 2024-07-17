/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/17 14:44:58 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

void	ft_pwd(t_data data)
{
	char		*pwd;
	char		*aux;

	aux = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		aux = get_env("PWD", data);
		if (aux)
			printf("%s\n", aux);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}	
}

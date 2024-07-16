/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:51 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/16 17:41:12 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/minishell.h"

char	*get_env(char *to_find, t_data cmd)
{
	t_node *aux;

	aux = cmd.env.start;
	while (aux)
	{
		if (ft_strncmp(to_find, aux->value, 3) == 0)
			return (aux->value);
		aux = aux->next;
	}
	return (NULL);
}
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

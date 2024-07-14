/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:47:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/12 11:47:14 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_exec
{
	pid_t		pid1;
	int			fd;
	int			tube[2];
	char		*cmd;
	char		**path;
}	t_exec;

// global variable
int		err;
// main
void	child(t_exec exec, char **argv, char **env);

#endif

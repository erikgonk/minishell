/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:47:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/24 17:49:59 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define ONE_CMD 0
# define ONE_REDIR 1
# define MORE_REDIR 2

typedef struct s_childs
{
	pid_t			pid1;
	int				fd;
	int				tube[2];
	struct t_childs	*next;
}	t_childs;

typedef struct s_exec
{
	char		*cmd;
	char		**path;
	s_childs	*childs;
	int			i;
}	t_exec;

// main
int		exec(t_pipex pipex);
char	*check_cmd(char **paths, char *argv);
void	child(t_exec exec, char **argv, char **env);

#endif

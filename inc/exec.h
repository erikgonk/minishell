/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:47:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/30 19:02:09 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "builtins.h"

typedef struct s_exec
{
	char		**env;
	char		*cmd;
	char		**path;
	char		**argv;
	int			i;
	int			p[2];
	int			fd;
}	t_exec;

// main
char	*check_cmd(char **paths, char *argv);
void	child(t_exec exec, char **argv, char **env);

// cmd
int			cmds(t_data *data, t_exec *exec);
void		ft_init_exec(t_exec *exec);
int			ft_env_to_cmd(t_node *env, t_exec *exec, int size, int i);
int			ft_count_list_elems_str(t_node *env);
static int	ft_lst_size(t_cmds *cmd);

// utils
char	*ft_get_path(t_data *data, t_cmds *cmd);
void	close_pipes(int fd[2]);

#endif

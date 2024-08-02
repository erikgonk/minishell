/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:47:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/01 17:12:56 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "builtins.h"
# include "redirs.h"

typedef struct s_exec
{
	char		**env;
	char		**path;
	char		*cmd;
	int			p[2];
	int			fd;
	int			g_exit;
	t_lex       *lexer;
	t_cmds		*cmd_t;
	t_env		*env_t;
}	t_exec;

// exec
static int	ft_builtins(t_exec *exec);
int	ft_executor(t_data	*data);

// cmd
int			cmds(t_data *data, t_cmds *cmd, t_exec *exec);
void	ft_find_exit_status(t_data *data, pid_t *kids, int	size);
int	ft_childs(t_data *data, t_cmds *cmd, t_exec *exec);
int	ft_innit_cmd(t_data *data, t_cmds *cmd, t_exec *exec);
void	ft_middle_cmd(t_data *data, t_cmds *cmd, t_exec *exec);

//cmd_utils
void		ft_init_exec(t_exec *exec);
int			ft_lst_size(t_cmds *cmd);
int			ft_count_list_elems_str(t_node *env);
int			ft_env_to_cmd(t_node *env, t_exec *exec, int size, int i);

// cmd_utils2
void	close_pipes(int fd[2]);
void	ft_get_cmd_help(t_exec *exec, t_cmds *cmd, int i);
char	*ft_get_cmd(t_data *data, t_cmds *cmd, t_exec *exec);

#endif

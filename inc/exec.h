/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:47:58 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 16:06:05 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec
int				ft_builtins(t_exec *exec);
int				ft_executor(t_data *data, t_exec *exec, t_cmds *cmd);

// cmd
int				ft_cmds(t_data *data, t_exec *exec, t_cmds *cmd);
void			ft_find_exit_status(t_data *data, pid_t *kids, int size);
int				ft_childs(t_data *data, t_cmds *cmd, t_exec *exec);
int				ft_forking(t_data *data, t_cmds *cmd, t_exec *exec);
void			ft_middle_cmd(t_data *data, t_cmds *cmd, t_exec *exec);


//cmd_utils1
int				ft_env_to_cmd(t_node *env, t_exec *exec, int size, int i);
int				ft_count_list_elems_str(t_node *env);
int				ft_lst_size(t_cmds *cmd);
void			ft_init_exec(t_exec *exec);

// cmd_utils2
char			*ft_get_cmd(t_data *data, t_cmds *cmd, t_exec *exec);
void			ft_close_pipes(int fd[2]);

// Signals
void			ft_sig_c_hdoc(int sig, t_data *data);
void			ft_sig_c(int sig);
int				ft_get_stt(int flag, int val);
// int				get_stt(int flag, int val); // do not show ^C, ^\...

#endif

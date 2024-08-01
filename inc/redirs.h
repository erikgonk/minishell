/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:35:52 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/01 14:36:56 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "minishell.h"
# include "builtins.h"
# include "exec.h"

// redirs
void    ft_redirections(t_data *data, t_cmds *cmd, t_exec *exec);
void    ft_redir_to_fd(t_data *data, t_cmds *cmd, int *fd, t_exec *exec);
void    ft_middle_redirs(t_data *data, t_cmds *cmd, int *fd, t_exec *exec);
void    ft_inni_redirs(t_lex *lex);

#endif

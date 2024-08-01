/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:37:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/01 18:07:35 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"
#include "../../inc/exec.h"
#include "../../inc/redirs.h"

void	ft_inni_redirs(t_lex *lex)
{
	int		i;

	lex->in = 0;
	lex->out = 1;
	while (lex)
	{
		i = access(lex->literal, R_OK);
		lex->err = 0;
		if (i != 0)
		{
			ft_printf("minish: %s: Permission denied\n", lex->literal);
			lex->err = -1;
		}
		else if (lex->type == T_REDIR_IN || lex->type == T_HEREDOC)
			lex->in = open(lex->literal, O_RDONLY);
		else if (lex->type == T_REDIR_OUT)
			lex->out = open(lex->literal, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (lex->type == T_APPEND)
			lex->out = open(lex->literal, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		lex = lex->next;
	}
}

void	ft_middle_cmd(t_data *data, int *fd, t_exec *exec)
{
	exec->fd = dup(exec->p[0]);// reads info from file before
	close_pipes(exec->p);
	pipe(exec->p);// creates again p[0] & p[1]
	dup2(*fd, 0);
	close_pipes(exec->p);
	close(*fd);
}	

void	ft_redir_to_fd(t_data *data, int *fd, t_exec *exec)
{
	if (!cmd->prev)
	{
		dup2(*fd, 1);// writes in the pipe
		close_pipes(exec->p);
		close(*fd);
	}
	else if (cmd->next)
		ft_middle_cmd(data, fd, exec);
	else
	{
		dup2(*fd, 0);// writes in the terminal
		close_pipes(exec->p);
		close (*fd);
	}
}

void	ft_redirections(t_data *data, t_cmds *cmd, t_exec exec)
{
	if (cmd->redirections)
		ft_inni_redirs(cmd->redirections);// open fds on the cmd lst
	while (cmd->redirections)
	{
		// see how to delete the fd before this
		if (cmd->redirections->err == -1)
			return ;
		if (cmd->redirections->type == T_REDIR_IN || cmd->redirections->type == T_HEREDOC)
			ft_redir_to_fd(data, &cmd->redirections->in, exec);
		else if (cmd->redirections->type == T_REDIR_OUT || cmd->redirections->type == T_APPEND)
			ft_redir_to_fd(data, &cmd->redirections->out, exec);
		cmd->redirections = cmd->redirections->next;
	}
}

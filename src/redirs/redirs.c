/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:37:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/05 14:31:56 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	ft_inni_redirs(t_lex *lex)
{
	int	i;

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
		else if (lex->type == T_APPEND)
			lex->out = open(lex->literal, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (lex->type == T_REDIR_OUT)
			lex->out = open(lex->literal, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		lex = lex->next;
	}
}

void	ft_middle_redirs(t_data *data, t_cmds *cmd, int *fd, t_exec *exec)
{
	exec->fd = dup(exec->p[0]); // reads info from file before
	close_pipes(exec->p);
	pipe(exec->p); // creates again p[0] & p[1]
	dup2(*fd, 0);
	close_pipes(exec->p);
	close(*fd);
}

void	ft_redir_to_fd(t_data *data, t_cmds *cmd, int *fd, t_exec *exec)
{
	if (!cmd->prev)
	{
		dup2(*fd, 1); // writes in the pipe
		close_pipes(exec->p);
		close(*fd);
	}
	else if (cmd->next)
		ft_middle_redirs(data, cmd, fd, exec);
	else
	{
		dup2(*fd, 0); // writes in the terminal
		close_pipes(exec->p);
		close(*fd);
	}
}

void	ft_redirections(t_data *data, t_cmds *cmd, t_exec *exec)
{
	if (exec->cmd_t->redirections)
		ft_inni_redirs(exec->cmd_t->redirections); // open fds on the cmd lst
	while (exec->cmd_t->redirections)
	{
		if (exec->cmd_t->redirections->err == -1)
			exit(1);
		if (exec->cmd_t->redirections->type == T_REDIR_IN
			|| exec->cmd_t->redirections->type == T_HEREDOC)
			ft_redir_to_fd(data, exec->cmd_t, &exec->cmd_t->redirections->in,
				exec);
		else if (exec->cmd_t->redirections->type == T_REDIR_OUT
			|| exec->cmd_t->redirections->type == T_APPEND)
			ft_redir_to_fd(data, exec->cmd_t, &exec->cmd_t->redirections->out,
				exec);
		if (exec->cmd_t->redirections->next)
		{
			close(exec->cmd_t->redirections->in);
			close(exec->cmd_t->redirections->out);
		}
		exec->cmd_t->redirections = exec->cmd_t->redirections->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:37:05 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/09 14:00:47 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

static int	ft_redirs_err(t_cmds *cmd, int i)
{
	if (cmd->redirections->type != T_HEREDOC &&
			!access(cmd->redirections->literal, F_OK))
		i = access(cmd->redirections->literal, R_OK);
	if (i != 0)
	{
		ft_printf(2, "minish: %s: Permission denied\n", cmd->redirections->literal);
		close (cmd->in);
		close (cmd->out);
		cmd->in = -1;
		cmd->out = -1;
		return (-1);
	}
	return (0);
}

void	ft_innit_redirs(t_cmds *cmd, t_lex *lex)
{
	while (cmd)
	{
		lex = cmd->redirections;
		cmd->in = 0;
		cmd->out = 1;
		while (lex)
		{
			ft_redirs_err(cmd, 0);
			if (cmd->in != -1 && cmd->redirections->type == T_REDIR_IN)
				cmd->in = open(cmd->redirections->literal, O_RDONLY);
			else if (cmd->out != -1 && cmd->redirections->type == T_APPEND)
				cmd->out = open(cmd->redirections->literal, O_WRONLY | O_APPEND | O_CREAT, 0644);
			else if (cmd->out != -1 && cmd->redirections->type == T_REDIR_OUT)
				cmd->out = open(cmd->redirections->literal, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (cmd->redirections->type == T_HEREDOC)
			{
				if (cmd->in != 0)
				{
					close (cmd->in);
					cmd->in = 0;
				}
			}
			lex = lex->next;
		}
		if (cmd->hdoc && cmd->in == 0)
			cmd->in = cmd->hdoc;
		cmd = cmd->next;
	}
}

void	ft_redirections(t_cmds *cmd)
{
	if (cmd->in != 0)
	{
		dup2(cmd->in, 0);
		close (cmd->in);
	}
	if (cmd->out != 1)
	{
		dup2(cmd->out, 1);
		close (cmd->out);
	}
}

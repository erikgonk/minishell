/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:07:41 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/12 11:43:58 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static int	print_error(char *str, int exit)
{
	printf("mish: error: %s\n", str);
	return (exit);
}

static int	parent_hdoc(int fd[2])
{
	int	child;

	close(fd[1]);
	wait(&child);
	if (WIFEXITED(child))
		return (fd[0]);
	close(fd[0]);
	return (-1);
}

static void	child_hdoc(int fd[2], char *lim, t_data *data)
{
	char	*input;

	signal(SIGINT, &ctrlc_hdoc);
	input = readline("> ");
	if (!input)
		printf("mish: hdoc delimited by eof (wanted '%s')\n", lim);
	else
	{
		while (my_strcmp(input, lim))
		{
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
			free(input);
			input = readline("> ");
			if (!input)
			{
				printf("mish: hdoc delimited by eof (wanted '%s')\n", lim);
				break ;
			}
		}
		free(input);
	}
	close(fd[1]);
	clean_shell(data);
	exit(0);
}

static int	fork_hdoc(t_cmds *cmd, t_lex *redirs, t_data *data)
{
	int	fd[2];
	int	pid;

	if (cmd->hdoc)
		close(cmd->hdoc);
	if (pipe(fd) == -1)
		exit(print_error("pipe", 1));
	pid = fork();
	if (pid < 0)
		exit(print_error("fork", 1));
	else if (pid == 0)
		child_hdoc(fd, redirs->literal, data);
	else
		cmd->hdoc = parent_hdoc(fd);
	if (cmd->hdoc < 0)
		return (1);
	return (0);
}

int	execute_hdoc(t_cmds *cmds, t_data *data)
{
	t_lex	*redirs;

	while (cmds)
	{
		redirs = cmds->redirections;
		while (redirs)
		{
			if (redirs->type == T_HEREDOC)
			{
				if (fork_hdoc(cmds, redirs, data))
					return (1);
			}
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

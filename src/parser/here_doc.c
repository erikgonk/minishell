/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:07:41 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 11:44:33 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

//not the final error printing function, need better management
static int      print_error(char *str, int exit)
{
    printf("mish: error: %s\n", str);
    return (exit);
}

//handling signals inside the hdoc
void     ctrlc_hdoc(int signum)
{
    (void)signum;
    write(2, "\n", 1);
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
        exit(1);
    kill(0, SIGINT);
}

static int      parent_hdoc(int fd[2])
{
    int     child;

    close(fd[1]); //closing the write end of the pipe bc we finished writing
    wait(&child); //waiting for the child process to finish
    if (WIFEXITED(child)) // if process returns with no error we return the read end of the pipe
        return(fd[0]);
    close(fd[0]); // if not, there was an error, so we close the read end and return -1 to indicate error
    return (-1);
}

static void     child_hdoc(int fd[2], char *lim)
{
    char    *input;

    signal(SIGINT, &ctrlc_hdoc);
    input = readline("> ");
    if (!input)
        printf("mish: warning: here-document delimited by end-of-file (wanted '%s')\n", lim);
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
                printf("mish: warning: here-document delimited by end-of-file (wanted '%s')\n", lim);
                break ;
            }
        }
        free(input);
    }
    close(fd[1]);
    exit (0);
}

static int     fork_hdoc(t_cmds *cmd, t_lex *redirs)
{
    int fd[2];
    int pid;

    if (cmd->hdoc)
        close(cmd->hdoc);
    if (pipe(fd) == -1)
        exit(print_error("pipe", 1));
    pid = fork();
    if (pid < 0)
        exit(print_error("fork", 1));
    else if (pid == 0)
        child_hdoc(fd, redirs->literal);
    else
        cmd->hdoc = parent_hdoc(fd);
    if (cmd->hdoc < 0)
        return (1);
    return (0);
}

/**
 * Should happen before any execution and other redir handling. 
 * Will iterate through all cmds nodes and its redirection list to search for hdocs.
 * If hdoc is found, it calls to create a pipe which we can write to.
 * The command will only read the input from the last hdoc.
*/
int execute_hdoc(t_cmds *cmds)
{
	t_lex *redirs;
	
	while (cmds)
	{
		redirs = cmds->redirections;
		while (redirs)
		{
			if (redirs->type == T_HEREDOC)
			{
				if (fork_hdoc(cmds, redirs))
					return (1);
			}
		redirs = redirs->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
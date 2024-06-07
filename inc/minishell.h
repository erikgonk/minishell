/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:47:55 by erigonza          #+#    #+#             */
/*   Updated: 2024/05/26 16:47:58 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "mish> "

typedef struct s_data
{
    t_cmds      *cmd; //list of the parsed line
    t_lex       *lexer;
    char        **paths;
    int         heredoc;
    int         pipes;
    int         *pid;
    int         err_status;
}   t_data;

// write, read, close, access, pipe, dup, dup2, execve, fork
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
// malloc, free, exit
# include <stdlib.h>
// open, unlink
# include <fcntl.h>
// waitpid, wait
# include <sys/wait.h>
// strerror 
# include <string.h>
// perror
# include <stdio.h>
// libft 
# include "../src/libft/inc/libft.h"

// main

#endif

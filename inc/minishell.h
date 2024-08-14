/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:47:55 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/14 12:50:59 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

// write, read, close, access, pipe, dup, dup2, execve, fork
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
// malloc, free, exit
# include <stdlib.h>
// open, unlink
# include <fcntl.h>
// waitpid, wait
# include <sys/wait.h>
// strerror
# include <string.h>
// perror
# include <signal.h>
# include <stdio.h>
// libft
# include "../src/libft/inc/libft.h"
# include "env.h"
# include "parser.h"
# include "tokenizer.h"
# include "utils.h"
# include <readline/history.h>
# include <readline/readline.h>

# define PROMPT "mish> "
# define C_LESS '<'
# define C_GREAT '>'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '\"'

extern int			g_signal;

/*-----------------Enums------------------*/
typedef enum t_token
{
	T_PIPE = 1,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_WORD,
}					t_token;

typedef enum t_builtin
{
	PWD = 1,
	ECHO,
	CD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NO_BUILTIN,
}					t_builtin;

/*--------------Structures----------------*/
typedef struct s_lex
{
	enum t_token	type;
	char			*literal;
	int				index;
	int				in;
	int				out;
	int				err;
	struct s_lex	*next;
}					t_lex;

typedef struct s_parser
{
	t_lex			*lexer;
	t_lex			*redirections;
	t_data			*data;
	int				redir_count;
}					t_parser;

typedef struct s_expander
{
	char			*pre_and_exp;
	char			*finished;
	char			*exp_var;
	char			*pre_exp;
	char			*var;
	int				pos;
	int				start;
	int				status;
}					t_expander;

typedef struct s_cmds
{
	char			**cmd;
	enum t_builtin	builtin;
	int				in;
	int				out;
	int				hdoc;
	t_lex			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

typedef struct s_node
{
	char			*var;
	char			*str;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	t_node			*start;
	t_node			*end;
	char			*pwd;
	char			*oldpwd;
	char			*homedir;
}					t_env;

typedef struct s_data
{
	char			*input;
	t_lex			*lexer;
	t_cmds			*cmds;
	t_parser		*parser;
	t_env			*env;
	int				hdoc_count;
	int				*pid;
	int				g_exit;
	int				printed_error;
	int				pipes;
}					t_data;

typedef struct s_exec
{
	char			**env;
	char			**path;
	char			*cmd;
	int				p[2];
	int				fd;
	int				g_exit;
	int				flag_b;
	t_lex			*lexer;
	t_cmds			*cmd_t;
	t_env			*env_t;
	t_data			*data_t;
}					t_exec;

/*---------main + main utils----------*/

void				mini_loop(t_data *data);
char				*clean_input(char *input);
char				*get_input(t_data *data);
int					init_minishell(t_env *env, t_data *data, char **envp);
void				free_env(t_env *env);

//for testing + printing tests
void				print_cmds(const t_data *data);
void				clean_shell(t_data *data);

int					execute_hdoc(t_cmds *cmds, t_data *data);
void				ctrlc_hdoc(int signum);

int					ft_get_stt(int flag, int val);
void				ft_sig_c(int sig);
void				ft_child_sig(int sig);

#endif

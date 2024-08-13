/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:47:55 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 14:27:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <signal.h>
// libft 
# include "../src/libft/inc/libft.h"
# include "parser.h"
# include "utils.h"
# include "expander.h"
# include "env.h"
# include "tokenizer.h"

# include <readline/readline.h> 
# include <readline/history.h>

# define PROMPT "mish> "
# define C_LESS '<'
# define C_GREAT '>'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '\"'

extern int g_signal; 

/*-----------------Enums------------------*/
typedef enum e_token
{
	T_PIPE = 1,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_WORD,
}   e_token;

typedef enum e_builtin
{
    PWD = 1,
    ECHO,
    CD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    NO_BUILTIN,
}   e_builtin;

/*--------------Structures----------------*/
typedef struct s_lex
{
	enum e_token	type; //type of token
	char			*literal; //the string literal (eg. "cat -e")
	int				index; //position in the linked list
    int				in;// < && <<
	int				out;// > && >>
	int				err;// error opening the redir -> err = -1
	struct s_lex	*next;
}	t_lex;

typedef struct s_parser
{
    t_lex   *lexer;
    t_lex   *redirections;
    t_data  *data;
    int     redir_count;
}   t_parser;

typedef struct s_expander
{
    char    *pre_and_exp;
    char    *finished;
    char    *exp_var;
    char    *pre_exp;
    char    *var;
    int     pos;
    int     start;
    int     status;
}   t_expander;

typedef struct s_cmds
{
    char            **cmd; //the full command with its flags
    enum e_builtin  builtin; //builtin spesification 
	int				in;
	int				out;
	int				hdoc;
    t_lex           *redirections; //structure with redirection information (type of redir and the corresponding file name)
    struct s_cmds   *next;
    struct s_cmds   *prev;
}   t_cmds;

typedef struct s_node
{
    char            *var;
    char            *str;
    struct s_node   *next;
}   t_node;

typedef struct s_env
{
    t_node      *start;
    t_node      *end;
    char        *pwd;
    char        *oldpwd;
    char        *homedir; //for cd ~
}   t_env;

typedef struct s_data
{
    char        *input; // users input string
    t_lex       *lexer; // pointer to the linked list of tokens
    t_cmds      *cmds; //pointer to the command linked list
    t_parser    *parser; // pointer to the parser util structure
    t_env       *env; //pointer to the environment list
    int         hdoc_count; // How many heredocs are present in the input
    int         *pid; // Pointer to array of the pids
    int         g_exit; // "global" return error number
    int         printed_error; //to check whether an error message has already been printed (syntax errors)
    int         pipes; // NUmber of pipes present to know for how many child processes needed
}   t_data;

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
	t_data		*data_t;
}	t_exec;

/*---------main + main utils----------*/
extern int g_signal;

void    mini_loop(t_data *data);
char    *clean_input(char *input);
char    *get_input(t_data *data);
int     init_minishell(t_env *env, t_data *data, char **envp);
void    free_env(t_env *env);

//for testing + printing tests
void    print_cmds(const t_data *data);
void    clean_shell(t_data *data);

int     execute_hdoc(t_cmds *cmds, t_data *data);
void    ctrlc_hdoc(int signum);

int     ft_get_stt(int flag, int val);
void	ft_sig_c(int sig);
void	ft_child_sig(int sig);

#endif

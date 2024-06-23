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

# define PROMPT "mish> "
# define C_LESS '<'
# define C_GREAT '>'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '"'

/*-----------------Enums------------------*/
typedef enum e_token
{
	T_PIPE = 1,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_WORD,
};

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
};

/*--------------Structures----------------*/
typedef struct s_lex
{
	enum e_token	type; //type of token
	char			*literal; //the string literal (eg. "cat -e")
	int				index; //position in the linked list
	struct s_lex	*next;
}	t_lex;

typedef struct s_parser
{
    t_lex   *lexer;
    t_lex   *redirections;
    t_data  *data;
    int     redir_count;
}   t_parser;

typedef struct s_cmds
{
    char            **cmd; //the full command with its flags
    enum e_builtin  builtin; //builtin spesification 
    int             redirs; //number of redirections for this current command
    t_lex           *redirections; //structure with redirection information (type of redir and the corresponding file name)
    struct s_cmds   *next;
    struct s_cmds   *prev;
}   t_cmds;

typedef struct s_data
{
    char        *input;
    t_lex       *lexer;
    t_cmds      *cmds;
    char        **envp;
    char        **exp_env;
    char        **paths;
    int         heredoc;
    int         redir_counter;
    int         *pid;
    int         g_exit;
    bool        reset;
}   t_data;

/*------------Main--------------*/
void    data_reset(t_data *data, char **envp);
void    main_loop(t_data *data, char **envp);

/*-----------Lexer--------------*/
t_lex	*tokenizer(char *input);
int     token_length(char *input);
void    add_index(t_lex *tokens);
void    free_tokens(t_lex *tokens);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length);

/*-----------Parser-------------*/
void        handle_redirs(t_data *data, t_parser *parser);
void        add_redir(t_parser *parser, t_lex *tmp);
int         parsing(t_data *data);
t_cmds      *make_cmd(t_data *data, t_parser *parser);
t_cmds      *new_cmd(char **str, int redir_count, t_lex *redir);
void        add_cmd_node(t_cmds **head, t_cmds *new);
t_parser    init_parser(t_lex *lexer, t_data *data);
void        count_pipes(t_data *data);
int         count_args(t_lex *tokens);

/*------------Utils--------------*/
char    **split_envp(char **envp);
t_lex   *lex_new_node(char *str, enum e_token token);
void    lex_clear_one(t_lex **del);
void    lex_del_first(t_lex **del);
void    lex_del_node(t_lex **lst, int index);
void    lex_add_node(t_lex *new, t_lex **redir);

#endif

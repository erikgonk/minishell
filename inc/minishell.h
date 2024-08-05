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
#include <readline/readline.h> 
#include <readline/history.h>

# define PROMPT "mish> "
# define C_LESS '<'
# define C_GREAT '>'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '"'

typedef struct s_data t_data;
typedef struct s_env t_env;

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
    t_lex           *redirections; //structure with redirection information (type of redir and the corresponding file name)
    struct s_cmds   *next;
    struct s_cmds   *prev;
}   t_cmds;

typedef struct s_node
{
    char    *var;
    char    *str;
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

/*------------Main--------------*/
void    mini_loop(t_data *data);
char    *clean_input(char *input);
char    *get_input(t_data *data);
int     init_minishell(t_env *env, t_data *data, char **envp);


//lex_lst.c
int lex_lstlen(t_lex *tokens);
void    lex_free(t_lex **lst);
t_lex   *lex_lstlast(t_lex *tokens);
void    lex_addback(t_lex **lst, t_lex *node);
void    lex_clearone(t_lex **lst);
void    lex_delfirst(t_lex **lst);
void    lex_delone(t_lex **lst, int del);
t_lex   *lex_new(char *str, int token);

//input_check.c
int input_check(char *input, t_data *data);
int	arg_count(char *str, char c);
int	quote_checker(char *str);
int	quotes(char *input, int *i, int flag, char c);
int	change_flag(int flag);

//cmd_lst.c
t_cmds  *cmds_lstnew(char **command);
t_cmds  *cmds_lstlast(t_cmds *lst);
void    cmds_addback(t_cmds **lst, t_cmds *node);
void clean_cmds(t_cmds **cmds);

//tokenize.c
int  find_type(char *literal);
int token_length(char *input);
t_lex *fill_tokens(t_lex *tokens, char *input, int length, t_data *data);
t_lex	*tokenizer(char *input, t_data *data);

//token_utils.c
void    add_index(t_lex *tokens);
int is_hdoc_present(t_lex *tokens);
int  find_next_redir(char *literal, int i);
int     check_syntax_and_hdoc(t_data *data, t_lex *tokens, char *input, t_lex *new, int i);
t_lex *make_token(int length, char *input, t_lex *tokens, t_data *data);

//token_checks.c
int check_redirs(t_lex **lst, t_data *data);
int check_pipes(t_lex **lst, t_data *data);
int    check_tokens(t_data *data, t_lex **lst);


/*-----------Parser-------------*/
int    parser(t_data *data);
t_cmds  *create_cmd(t_parser *parser);
t_cmds *new_cmd(char **str, t_parser *parser);
int get_builtin(char *str);

//parser_utils.c
void        on_error(char *str, int fd, t_data *data);
void        count_pipes(t_lex *lexer, t_data *data);
t_parser    init_parser(t_lex *lexer, t_data *data);
int         count_arguments(t_lex *lexer);

//parser_redir.c
void    new_redir(t_lex *tmp, t_parser *parser);
void    add_redir(t_parser *parser);

//expand.c
char *expand_filename(char *filename, t_data *data);
char **expand_cmd(char **cmd, t_data *data);
void    expand(t_data *data, t_cmds *cmds);
char *expand_single(char *str, t_data *data);

//status_utils.c
int get_status(char c, int current);
void append_to_finished(t_expander *exp, char *str);
void no_quote_exp(char *str, t_expander *exp, t_data *data);
void single_quote_exp(char *str, t_expander *exp);
void double_quote_exp(char *str, t_expander *exp, t_data *data);

//var_expand.c
char *find_var(char *str, t_expander *exp);
char *expand_var(char *var, t_data *data);

//env.c
char    *extract_str(char *envstr);
char    *extract_var(char *envstr);
t_node  *init_node(char *var, char *str);
void    add_to_env(t_node *node, t_env *env);
int    transform_env(t_env *env, char **envp);

//set_env.c
int set_standard_env(t_env *env, char *shlvl);
int set_env(t_env *env, char *var, char *str);
int     in_env(char *var, t_env env);
char    *get_env(char *var, t_env env);

void print_cmds(const t_data *data);
void    executor(t_data *data);
void    clean_shell(t_data *data);


#endif

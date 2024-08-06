#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_data       t_data;
typedef struct s_cmds       t_cmds;
typedef struct s_lex        t_lex;

//lex_lst.c
int     lex_lstlen(t_lex *tokens);
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

#endif
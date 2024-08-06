#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_data       t_data;
typedef struct s_parser     t_parser;
typedef struct s_lex        t_lex;
typedef struct s_cmds       t_cmds;

/*-----------Parser-------------*/
int     parser(t_data *data);
t_cmds  *create_cmd(t_parser *parser);
t_cmds  *new_cmd(char **str, t_parser *parser);
int     get_builtin(char *str);

/*-----------Parser_utils.c-------------*/
void        on_error(char *str, int fd, t_data *data);
void        count_pipes(t_lex *lexer, t_data *data);
t_parser    init_parser(t_lex *lexer, t_data *data);
int         count_arguments(t_lex *lexer);

/*-----------Parser_redir-------------*/
void        new_redir(t_lex *tmp, t_parser *parser);
void        add_redir(t_parser *parser);

#endif
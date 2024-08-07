#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef struct s_data       t_data;
typedef struct s_lex        t_lex;

/************tokenize.c*****************/
int     find_type(char *literal);
int     token_length(char *input);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length, t_data *data);
t_lex   *tokenizer(char *input, t_data *data);

/*********tokenize_utils.c**************/
void    add_index(t_lex *tokens);
int     is_hdoc_present(t_lex *tokens);
int     find_next_redir(char *literal, int i);
int     check_syntax_and_hdoc(t_data *data, t_lex *tokens, char *input, t_lex *new, int i);
t_lex   *make_token(int length, char *input, t_lex *tokens, t_data *data);

/*********tokenize_checks.c**************/
int     check_redirs(t_lex **lst, t_data *data);
int     check_pipes(t_lex **lst, t_data *data);
int     check_tokens(t_data *data, t_lex **lst);

#endif
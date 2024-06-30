#include "parser.h"

void    check_token(t_data *data, t_lex *lexer)
{
    data->g_exit = 258;
    if (lexer->type == T_REDIR_IN)
        on_error("Syntax error near unexpected token '<'\n", STDERR_FILENO, data);
    else if (lexer->type == T_REDIR_OUT)
        on_error("Syntax error near unexpected token '>'\n", STDERR_FILENO, data);
    else if (lexer->type == T_APPEND)
        on_error("Syntax error near unexpected token '>>'\n", STDERR_FILENO, data);
    else if (lexer->type == T_HEREDOC)
        on_error("Syntax error near unexpected token '<<'\n", STDERR_FILENO, data);
    else if (lexer->type == T_PIPE)
        on_error("Syntax error near unexpected token '|'\n", STDERR_FILENO, data);
}

void    count_pipes(t_lex *lexer, t_data *data)
{
    data->pipes = 0;
    while (lexer)
    {
        if (lexer->type == T_PIPE)
            data->pipes++;
        lexer = lexer->next;
    }
}

t_parser    init_parser(t_lex *lexer, t_data *data)
{
    t_parser    parser;

    parser.lexer = lexer;
    parser.redir_count = 0;
    parser.redirections = NULL;
    parser.data = data;
    return (parser);
}

int count_arguments(t_lex *lexer)
{
    int i;

    i = 0;
    while (lexer && lexer->type != T_PIPE)
    {
        if (lexer->type == T_WORD)
            i++;
        lexer = lexer->next;
    }
    return (i);
}
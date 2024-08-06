#include "../../inc/parser.h"

//idk ab this function
void    on_error(char *str, int fd, t_data *data)
{
    ft_putstr_fd(str, fd);
    mini_loop(data);
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
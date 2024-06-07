#ifndef PARSER_H
# define PARSER_H

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

typedef struct s_parser
{
    t_lex   *lexer;
    t_lex   *redirections;
    t_data  *data;
    int     redir_count
}   t_parser;

typedef struct s_cmds
{
    char    **cmd; //the full command with its flags
    enum e_builtin   builtin; //builtin spesification 
    int     redir_count; //number of redirections
    t_lex   *redirs; //structure with redirection information (type of redir and the corresponding file name)
    t_lex   *lexer; // structure with all the tokens
    struct s_cmds *next;
    struct s_cmds *prev;
}   t_cmds;
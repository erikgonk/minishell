#include "parser.h"
#include "minishell.h"

/**
 * 1. Count pipes to know how many child processes to create. (pipes + 2)
 * 2. Checks whether the first token is a pipe, which is an error.
 * 3. Iterates through the list until found pipe
 */
int    parser(t_data *data)
{
    t_cmds      *node;
    t_parser    parser;

    if (!check_tokens(data, &data->lexer))
        return (0);
    count_pipes(data->lexer, data);
    while (data->lexer)
    {
        if (data->lexer && data->lexer->type == T_PIPE)
            lex_lstdelone(&data->lexer, data->lexer->index);
        parser = init_parser(data->lexer, data);
        node = create_cmd(&parser);
        if (!node)
            return (0);
        if (!data->cmds)
            data->cmds = node;
        else 
            cmd_lstaddback(&data->cmds, node);
        data->lexer = parser.lexer;
    }
    return (1);
}

t_cmds  *create_cmd(t_parser *parser)
{
    char    **str;
    int     arg_count;
    int     pos;
    t_lex   *tmp;

    add_redir(parser);
    arg_count = count_args(parser->lexer);
    str = (char **)malloc(sizeof(char *) + (arg_count + 1));
    if (!str)
        return (NULL);
    pos = 0;
    tmp = parser->lexer;
    while (arg_count > 0)
    {
        if (tmp->type == T_WORD)
        {
            str[pos++] = ft_strdup(tmp->literal);
            lex_lstdelone(&parser->lexer, tmp->index);
            tmp = parser->lexer;
            arg_count--;
        }
    }
    str[pos] = NULL; //make sure this is the correct place to put it
    return (new_cmd(str, parser));
}

t_cmds  *new_cmd(char **str, t_parser *parser)
{
    t_cmds  *node;

    node = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
    if (!node)
        return (NULL);
    node->builtin = get_builtin(str[0]);
    node->redirections = parser->redirections;
    node->cmd = str;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

int get_builtin(char *str)
{
    if (ft_strcmp(str, "cd") == 0)
		return (CD);
	else if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(str, "env") == 0)
		return (ENV);
    else if (ft_strcmp(str, "echo") == 0)
        return (ECHO);
	else if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	else
		return (NULL);
}
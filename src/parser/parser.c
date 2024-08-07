#include "../../inc/parser.h"

int    parser(t_data *data)
{
    t_cmds      *node;
    t_parser    parser;

    node = NULL;
    count_pipes(data->lexer, data);
    while (data->lexer)
    {
        if (data->lexer && data->lexer->type == T_PIPE)
            lex_delone(&data->lexer, data->lexer->index);
        parser = init_parser(data->lexer, data);
        node = create_cmd(&parser);
        if (!node)
            return (0);
        if (!data->cmds)
            data->cmds = node;
        else 
            cmds_addback(&data->cmds, node);
        data->lexer = parser.lexer;
    }
    return (1);
}

//this function is too log rip
t_cmds  *create_cmd(t_parser *parser)
{
    char    **str;
    int     arg_count;
    int     i;
    t_lex   *tmp;

    add_redir(parser);
    arg_count = count_arguments(parser->lexer);
    str = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!str)
        return (NULL);
    i = 0;
    tmp = parser->lexer;
    while (i < arg_count)
    {
        if (tmp->type == T_WORD && tmp->literal)
        {
            str[i] = ft_strdup(tmp->literal);
            lex_delone(&parser->lexer, tmp->index);
            tmp = parser->lexer;
        }
        i++;
    }
    str[i] = NULL;
    if (i == 0)
    {
        free(str);
        str = NULL;
    }
    return (new_cmd(str, parser));
}

t_cmds *new_cmd(char **str, t_parser *parser)
{
    t_cmds *node;

    node = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
    if (!node)
        return NULL;
    if (str)
    {
        node->cmd = str;
        if (str[0])
            node->builtin = get_builtin(str[0]);
        else
            node->builtin = NO_BUILTIN;
    }
    else
    {
        node->cmd = NULL;
        node->builtin = NO_BUILTIN;
    }
    if (parser)
        node->redirections = parser->redirections;
    else
        node->redirections = NULL;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

int get_builtin(char *str)
{
    if (my_strcmp(str, "cd") == 0)
		return (CD);
	else if (my_strcmp(str, "pwd") == 0)
		return (PWD);
	else if (my_strcmp(str, "export") == 0)
		return (EXPORT);
	else if (my_strcmp(str, "unset") == 0)
		return (UNSET);
	else if (my_strcmp(str, "env") == 0)
		return (ENV);
    else if (my_strcmp(str, "echo") == 0)
        return (ECHO);
	else if (my_strcmp(str, "exit") == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}
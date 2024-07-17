int check_redirs(t_lex **lst, t_data *data)
{
    if (((*lst)->type >= T_REDIR_IN && (*lst)->type <= T_APPEND) && (!(*lst)->next || (*lst)->next->type != T_WORD)
    {
        data->g_exit = 258;
        on_error("Error: Syntax error near unexpected token 'newline'", 258, data);
        return (0);
    }
    return (1);
}

int check_pipes(t_lex **lst, t_data *data)
{
    if ((*lst)->type == T_PIPE && ((!(*lst)->next) || ((*lst)->next->type != T_WORD && !((*lst)->next->type >= T_REDIR_IN && (*lst)->next->type <= T_APPEND))))
    {
        data->g_exit = 258;
        on_error("Syntax error near unexpected token '|'\n", 127, data);
        return (0);
    }
    return (1);
}

int    check_tokens(t_data *data, t_lex **lst)
{
    if (!(*lst))
        return (0);
    if ((*lst)->type == T_PIPE)
    {
        data->g_exit = 258;
        on_error("Syntax error near unexpected token '|'", 127, data);
        return (0);
    }
    while (*lst)
    {
        if (!check_redirs(lst, data) || !check_pipes(lst, data))
            return (0);
        lst = &(*lst)->next;
    }
    return (1);
}
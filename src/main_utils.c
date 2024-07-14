void    reset_data(t_data *data, char **envp)
{
    if (data->input)
        free(data->input);
    if (data->lexer)
        free_lex(data->lexer);
    if (data->parser)
        free_parser(data->parser);
    if (data->env)
        free_env(data->env);
    if (data->pipes > 0)
        free(data->pid);
    if (init_data(&data, envp) == -1)
    {
        printf("Failed allocating data structure");
        exit(1);
    }
}

int	init_data(t_data *data, char **envp)
{
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	data->g_exit = 0;
    data->cmds = NULL;
    data->lexer = NULL;
    data->pipes = 0;
    data->hdoc_count = 0;
    if (create_env(env, envp))
		exit(EXIT_FAILURE);
	return (0);
}

char    *get_input(int g_exit)
{
    char    *input;

    input = readline(PROMPT);
    if (input == NULL)
    {
        if (isatty(STDIN_FILENO))
            ft_putstr_fd("exit\n", 2);
        exit(g_exit);
    }
    else if (input && *input)
    {
        add_history(input);
        if (check_open_quotes(input))
        {
            ft_putstr_fd("minish: unclosed quotes\n", 2);
            input[0] = '\0';
        }
    }
    return (input);
}
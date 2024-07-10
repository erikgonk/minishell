void    reset_data(t_data *data, char **envp)
{
    if (data->input)
        free(data->input);
    if (data->lexer)
        free_lex(data->lexer);
    if (data->parser)
        free_parser(data->parser);
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
	if (init_env(&(data->env), envp) == -1)
		return (-1);
	if (init_env(&(data->exp), envp) == -1)
		return (-1);
	data->g_exit = 0;
    data->cmds = NULL;
    data->lexer = NULL;
    data->pipes = 0;
    data->hdoc_count = 0;
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

static int	init_env(char ***env, char **envp)
{
	int			i;
	int         size;
    
    size = array_len(envp);
	*env = ft_calloc(size + 1, sizeof(char *));
	if (!*env)
		return (-1);
	i = 0;
	while (i < size)
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
			return (array_free(env));
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

int array_len(char **arr)
{
    int len;

    len = 0;
    if (!arr || !*arr)
        return (0);
    while (arr[len])
        len++;
    return (len);
}
void    reset_data(t_data *data)
{
    if (data->input)
        free(data->input);
    if (data->lexer)
        free_lex(data->lexer);
    if (data->parser)
        free_parser(data->parser);
    if (data->pipes > 0)
        free(data->pid);
    init_data(data);
    mini_loop(data); //works as a sort of while loop by calling one another
}

/**
 * Initiate all the variables to null and call init_signals to start listening.
 */
void    init_data(t_data *data)
{
    data->cmds = NULL;
    data->lexer = NULL;
    data->pipes = 0;
    data->parser = NULL;
    data->hdoc_count = 0;
    init_signals(); //function to handle signals
}

/**
 * Prompt the user for input by calling readline.
 * Then carry out some checks. If the prompt was control C (exit), we exit. 
 * If the prompt was empty, we just free and prompt the user again. 
 * In reset data there will be a call to mini_loop again, 
 * so it will work as a loop of sorts.
 */
void    mini_loop(t_data *data)
{
    char    *tmp;

    tmp = readline(PROMPT);
    if (!tmp)
        exit(0);
    data->input = ft_strtrim(tmp, " \t\n\r");
    if (!data->input || !data->input[0])
    {
        free(tmp);
        free(data->input);
        mini_loop(data);
    }
    add_history(data->input);
    check_closed_quotes(data); //whether there are any unclosed quotes
    tokenize(data);
    check_tokens(data, &data->lexer); //check whether any error w. redirections (multiple pipes in a row etc. )
    parsing(data);
    prep_exec(data);//or just execute?
    dup2(data->in, STDIN_FILENO);
    dup2(data->out, STDOUT_FILENO);
    reset_data(data);
}
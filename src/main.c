
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

    if (argc != 1 || argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
    handle_signals();
	if (init_data(&data, envp) == -1)
    {
        printf("Failed allocating data structure");
        exit(1);
    }
	mini_loop(&data, envp);
	clean_shell(data);
	return (0);
}

void    mini_loop(t_data *data, char **envp)
{
    while(1)
    {
        data->input = get_input(data->g_exit);
        if (!data->input || !*(data->input))
            continue ;
        if (!tokenize(data->input))
            continue ;
        if (!check_tokens(data, &data->lexer))
            continue ;
        if (!parsing(data))
            continue ;
        if (!prep_exec(data))
            continue ;
        reset_data(data, envp);
    }
}

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		fd_printf(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void    handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
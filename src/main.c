
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    t_env   env;

    if (argc != 1 || argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
    handle_signals();
	if (init_data(&env, &data, envp) == -1)
    {
        printf("Failed allocating data structure");
        exit(1);
    }
	mini_loop(&data, envp);
	clean_shell(data);
	return (0);
}

void    main_loop(t_data *data)
{
    char    *input;
    t_lex   *first_token;
    t_cmds  *first_cmd;

    lexer = NULL;
    cmds = NULL;
    input = NULL;
    while (1)
    {
        reset_data(data);
        modify_termios();
        handle_signals();
        input = get_input(data->g_exit);
        parent_signals();
        if (input[0] == '\0')
            continue ;
        first_token = tokenizer(input);
        if (!first_token)
            continue ;
        first_cmd = parser(data);
        if (first_cmd)
            data->g_exit = execute(data);
    }
    rl_clear_history();
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
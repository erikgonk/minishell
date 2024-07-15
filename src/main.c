/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:59:03 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/15 10:59:08 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    t_env   env;

    if (argc != 1 || argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
    handle_signals(); //check whether you actually need this here or if enough to just add in main loop
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
        handle_signals(); //handle the main signals
        input = get_input(data);
        if (input[0] == '\0')
            continue ;
        first_token = tokenizer(input);
        if (!first_token)
            continue ;
        first_cmd = parser(data);
        if (first_cmd)
            data->g_exit = execute(data); // this needs revision
    }
    rl_clear_history();
}

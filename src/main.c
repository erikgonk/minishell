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
	init_minishell(&env, &data, envp);
	mini_loop(&data);
	clean_shell(&env, &data);
	return (0);
}

void    mini_loop(t_data *data)
{
    char    *input;

    input = NULL;
    while (1)
    {
        lex_free(&data->lexer);
        clean_cmds(data->cmds);
        input = clean_input(input);
        data->printed_error = 0;
        handle_signals(); //handle the main signals
        input = get_input(data);
        if (input[0] == '\0')
            continue ;
        data->lexer = tokenizer(input);
        if (!data->lexer)
            continue ;
        check_tokens(data, &data->lexer);
        if (parser(data))
            data->g_exit = execute(data); // updating the exit status w. the result from execute
    }
    rl_clear_history();
}

char    *clean_input(char *input)
{
    if (input)
        free(input);
    return (NULL);
}

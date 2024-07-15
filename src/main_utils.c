/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:59:20 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/15 10:59:32 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

char    *get_input(t_data *data)
{
    data->input = readline(PROMPT);
    if (data->input == NULL)
    {
        if (isatty(STDIN_FILENO))
            ft_putstr_fd("exit\n", 2);
        exit(data->g_exit);
    }
    else if (data->input)
    {
        add_history(data->input);
        data->g_exit = input_check(data->input);
        if (data->g_exit == 1 || data->g_exit == 258)
        {
            data->input[0] = '\0';
        }
    }
    return (data->input);
}

/**
 * Just some checks to make sure the program does not crash
 * if the user decides to be annoying and input too many 
 * arguments or use open quotes.
*/
int input_check(char *input)
{
    if (quote_checker(input))
    {
        ft_putstr_fd("minishell: open quotes\n", 2);
        return (258);
    }
    if (arg_count(input, ' ') > MAXARGS) //idk how many arguments should be limit here 
    {
        ft_putstr_fd("minishell: don't be crazy: too many arguments\n", 2);
        return (1);
    }
    if (ft_strlen(input) > 4096)
    {
        ft_putstr_fd("minishell: don't be annoying: the prompt is too long\n", 2);
        return (1);
    }
    return (0);
}

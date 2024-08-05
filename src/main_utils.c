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

int	init_minishell(t_env *env, t_data *data, char **envp)
{
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
	data->g_exit = 0;
    data->lexer = NULL;
    data->pipes = 0;
    data->input = NULL;
    data->hdoc_count = 0;
    data->printed_error = 0;
    data->cmds = NULL;
    data->env = NULL;
    data->parser = NULL;
    data->pipes = 0;
    data->pid = NULL;
    env->start = NULL;
    env->end = NULL;
    env->homedir = NULL;
    env->oldpwd = NULL;
    env->pwd = NULL;
    if (transform_env(env, envp)) //should not exit if environment is not found, shell should still be working (?)
		exit(1);
    data->env = env;
	return (0);
}

char    *get_input(t_data *data)
{
    data->input = readline("Mish> ");
    if (data->input == NULL)
    {
        if (isatty(STDIN_FILENO))
            printf("exit\n");
        exit(data->g_exit);
    }
    else if (data->input)
    {
        add_history(data->input);
        if (input_check(data->input, data))
            data->input[0] = '\0';
    }
    return (data->input);
}

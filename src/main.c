/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:59:03 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 15:59:59 by erigonza         ###   ########.fr       */
/*   Updated: 2024/08/12 16:34:29 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "../inc/exec.h"

int			g_signal = 0;

static void	check_exp(t_data *data)
{
	t_cmds	*tmp;

	tmp = data->cmds;
	while (tmp)
	{
		expand(data, tmp);
		tmp = tmp->next;
	}
}

static void	refresh_command(t_data *data)
{
	data->printed_error = 0;
	lex_free(&data->lexer);
	clean_cmds(&data->cmds);
	signal(SIGINT, &ft_sig_c);
}

void	mini_loop(t_data *data)
{
	char	*input;
	t_exec	exec;

	input = NULL;
	while (1)
	{
		refresh_command(data);
		input = clean_input(input);
		input = get_input(data);
		signal(SIGINT, SIG_IGN);
		if (input == NULL || input[0] == '\0')
			continue ;
		data->lexer = tokenizer(input, data, 0);
		if (!data->lexer)
			continue ;
		if (check_tokens(data, &data->lexer))
			parser(data);
		if (data->cmds && data->printed_error == 0)
		{
			check_exp(data);
			ft_init_exec(&exec, data);
			data->g_exit = ft_executor(data, &exec);
		}
	}
	rl_clear_history();
}

void	clean_shell(t_data *data)
{
	if (!data)
		return ;
	if (data->lexer)
		lex_free(&data->lexer);
	if (data->input)
		clean_input(data->input);
	if (data->cmds)
		clean_cmds(&data->cmds);
	if (data->env)
		free_env(data->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env	env;

	if (argc != 1 || argv[1])
	{
		printf("This program does not take arguments\n");
		exit(0);
	}
	signal(SIGQUIT, SIG_IGN);
	init_minishell(&env, &data, envp);
	mini_loop(&data);
	clean_shell(&data);
	return (0);
}

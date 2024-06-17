/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:25:56 by vaunevik          #+#    #+#             */
/*   Updated: 2024/06/05 14:26:02 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*static void main_loop(t_data *data, char **input)
{
    t_lex   tokens;

    while (1)
    {
        input = readline(PROMPT);
        if (!input)
            exit(0); //probably some better error management here
        if (ft_strlen(*input) == 0)
        {
            free(*input);
            continue ; //skipping the next steps, but prompting the user again
        }
        add_history(*input);
        check_open_quotes(*input); //checks whether all quotes are closed
        tokens = tokenizer(*input);
        parsing(&tokens, data); //will take the linked token list and convert to the parsing list
        execute(data); //idk how exactly this will work but yeah
    }
}*/

void    main_loop(t_data *data, char **envp)
{
    while (1)
    {
        data->input = readline(PROMPT);
        if (data->input == NULL)
        {
            ft_putstr_fd("exit", STDOUT_FILENO);
            exit(0);
        }
        if (data->input[0] == '\0')
        {
            data_reset(data, envp);
            continue ;
        }
        add_history(data->input);
        if (!check_closed_quotes(data->input)) //check whether all quotes are closed
        {
            on_error(data); //err handling
            data_reset(data, envp);
            continue;
        }
        if (!tokenize(data))
        {
            on_error(data) // some better error handling here
            data_reset(data, envp);
            continue;
        }
        parser(data);
        execute(data);
        data_reset(data, envp);
    }
}

static void init_data(t_data *data, char **envp)
{
    data->input = NULL;
    data->cmds = NULL;
    data->lexer = NULL;
    data->envp = envp;
    data->paths = split_envp(envp);
    data->heredoc = 0;
    data->pipes = 0;
    data->pid = NULL;
    data->err_status = 0;
}

void    data_reset(t_data *data, char **envp)
{
    if (data->input)
        free(data->input);
    if (data->cmds)
        free_cmds(&data->cmds);
    if (data->pid)
        free(data->pid);
    init_data(data, envp);
}

int main(int argc, char **argv, char **envp)
{
    t_data  data;

    (void)argv;
    if (argc != 1)
    {
        ft_putstr("This program does not take any arguments\n");
        return(ARG_ERROR);
    }
    init_data(&data, envp);
    main_loop(&data, envp);
    return (0);
}
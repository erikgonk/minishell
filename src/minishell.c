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

static void main_loop(t_data *data, char **input)
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
}

static void init_data(t_data *data, char **envp)
{
}

int main(int argc, char **argv, char **envp)
{
    t_data  data;
    char    *input;

    (void)argv;
    input = NULL;
    if (argc != 1)
        return(ARG_ERR);
    init_data(&data, envp);
    main_loop(&data, *input);
    return (0);
}
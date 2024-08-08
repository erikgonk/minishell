/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:59:03 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/07 15:42:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"
#include "../inc/exec.h"

char    *clean_input(char *input)
{
    if (input)
        free(input);
    return (NULL);
}

/*void    mini_loop(t_data *data)
{
    char    *input;

    input = NULL;
    while (1)
    {
        data->printed_error = 0;
        lex_free(&data->lexer);
        clean_cmds(&data->cmds);
        input = clean_input(input);
        handle_signals();
        input = get_input(data);
        if (input[0] == '\0')
            continue ;
        data->lexer = tokenizer(input, data);
        if (!data->lexer)
            continue ;
        if (check_tokens(data, &data->lexer))
            parser(data);
    }
    rl_clear_history();
}
*/

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    t_env   env;

    if (argc != 1 ||argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
	init_minishell(&env, &data, envp);
	mini_loop(&data);
	return (0);
} 
*/

void print_cmds(const t_data *data) 
{
    t_cmds *tmp_cmd;
    t_lex *tmp_redir;
    int i;

    if (!data || !data->cmds)
    {
        printf("No commands to print.\n");
        return;
    }

    tmp_cmd = data->cmds;
    while (tmp_cmd) 
    {
        printf("Command: ");
        if (tmp_cmd->cmd)
        {
            i = 0; 
            while (tmp_cmd->cmd[i]) 
            {
                printf("[%s] ", tmp_cmd->cmd[i]);
                i++;
            }
        }
        else
        {
            printf("(No command)");
        }
        printf("\n");
        
        printf("Builtin type: %i\n", tmp_cmd->builtin);

        if (tmp_cmd->redirections) 
        {
            printf("Redirections:\n");
            tmp_redir = tmp_cmd->redirections;
            while (tmp_redir) 
            {
                printf("  %s (Type: %d, Index: %d)\n", tmp_redir->literal, tmp_redir->type, tmp_redir->index);
                tmp_redir = tmp_redir->next;
            }
        }
        else
        {
            printf("(No redirections)\n");
        }
        printf("\n");
        tmp_cmd = tmp_cmd->next;
    }
}

static void    check_exp(t_data *data)
{
    t_cmds *tmp;

    tmp = data->cmds;
    while (tmp)
    {
        expand(data, tmp);
        tmp = tmp->next;
    }
//    print_cmds(data);
}


void    mini_loop(t_data *data)
{
    char    *input;
	t_exec	exec;

    input = NULL;
    while (1)
    {
        data->printed_error = 0;
        lex_free(&data->lexer);
        clean_cmds(&data->cmds);
        input = clean_input(input);
        signal(SIGINT, ft_sig_c);
        input = get_input(data);
        signal(SIGQUIT, SIG_IGN);
        if (input == NULL ||input[0] == '\0')
        {
            //printf("%i\n", data->g_exit);
            continue ;
        }
        data->lexer = tokenizer(input, data);
        if (!data->lexer)
            continue ;
        if (check_tokens(data, &data->lexer))
            parser(data);
        check_exp(data);
		ft_init_exec(&exec, data); // initializes t_exec
		data->g_exit = ft_executor(data, &exec, exec.cmd_t);
		data->g_exit = ft_get_stt(0, 0);
        /*print_cmds(data);*/
//        printf("%i\n", data->g_exit);
    }
    rl_clear_history();
}

void    clean_shell(t_data *data)
{
    if (data->lexer)
        lex_free(&data->lexer);
    if (data->input)
        clean_input(data->input);
    if (data->cmds)
        clean_cmds(&data->cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    t_env   env;

    if (argc != 1 ||argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
	init_minishell(&env, &data, envp);
	mini_loop(&data);
	return (0);
}

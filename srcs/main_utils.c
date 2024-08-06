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

/*static int  is_empty(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' || !(str[i] <= 13 && str[i] >= 9))
            return (1);
        i++;
    }
    return (0);
}*/

char    *get_input(t_data *data)
{
    data->input = readline("Mish> ");
    if (data->input == NULL)
    {
        ft_putendl_fd("exit", STDOUT_FILENO);
        free_env(data->env);
        exit(EXIT_SUCCESS);
    }
    else if (data->input)
    {
        add_history(data->input);
        if (input_check(data->input, data))
            data->input[0] = '\0';
    }
    return (data->input);
}

static void free_nodes(t_node **node)
{
    t_node  *tmp;
    t_node  *next;

    tmp = (*node);
    while (tmp)
    {
        next = tmp->next;  // Save the next node
        if (tmp->str)
            free(tmp->str);
        if (tmp->var)
            free(tmp->var);
        free(tmp);  // Free the current node
        tmp = next;  // Move to the next node
    }
    *node = NULL;  // Set the pointer to NULL to avoid dangling pointer
}

void free_env(t_env *env)
{
    if (env->start)
        free_nodes(&env->start);
    if (env->homedir)
        free(env->homedir);
    if (env->oldpwd)
        free(env->oldpwd);
    if (env->pwd)
        free(env->pwd);
    env->end = NULL;
    env->start = NULL;
}

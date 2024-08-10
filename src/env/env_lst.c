/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:36:54 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/15 14:36:58 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/env.h"

#include "../../inc/env.h"

char    *extract_str(char *envstr)
{
    int     i;
    int     start;
    int     end;
    char    *str;

    i = 0;
    while (envstr[i])
    {
        if (envstr[i] == '=' && envstr[i + 1] != ' ') //and other whitespace?
        {
            start = i + 1;
            end = ft_strlen(envstr);
            str = ft_substr(envstr, start, end);
            if (!str)
                return (NULL);
            return (str);
        }
        i++;
    }
    return (NULL);
}

char    *extract_var(char *envstr)
{
    int     i;
    int     start;
    int     end;
    char    *var;

    i = 0;
    start = 0;
    while (envstr[i])
    {
        if (envstr[i + 1] == '=')
        {
            end = i + 1;
            var = ft_substr(envstr, start, end);
            if (!var)
                return (NULL);
            return (var);
        }
        i++;
    }
    end = i;
    var = ft_substr(envstr, start, end);
    return (var);
}

t_node  *init_node(char *var, char *str)
{
    t_node  *new;

    new = ft_calloc(1, sizeof(t_node));
    if (!new)
        return (NULL);
    new->var = var;
    new->str = str;
    new->next = NULL;
    return (new);
}

void    add_to_env(t_node *node, t_env *env)
{
    if (!env->start)
    {
        env->start = node;
        env->end = node;
    }
    else
    {
        env->end->next = node;
        env->end = node;
    }
}

int    transform_env(t_env *env, char **envp)
{
    t_node  *node;
    int     i;
    char    *var;
    char    *str;

    i = 0;
    while (envp[i])
    {
        var = extract_var(envp[i]);
        str = extract_str(envp[i]);
        node = init_node(var, str);
        add_to_env(node, env);
        i++;
    }
    if (set_standard_env(env, get_env("SHLVL", *env)))
                return (1);
        return (0);
}

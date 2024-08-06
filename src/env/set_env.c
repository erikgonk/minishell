/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:58:53 by vaunevik          #+#    #+#             */
/*   Updated: 2024/07/18 11:58:57 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/env.h"

int set_standard_env(t_env *env, char *shlvl)
{
    int i;

    i = 1;
    if (set_env(env, "OLDPWD", NULL))
        return (i);
    if (in_env("PWD", *env) && get_env("PWD", *env))
        env->pwd = ft_strdup(get_env("PWD", *env));
    if (in_env("OLDPWD", *env) && get_env("OLDPWD", *env))
        env->oldpwd = ft_strdup(get_env("OLDPWD", *env));
    if (in_env("HOME", *env) && get_env("HOME", *env))
        env->homedir = ft_strdup(get_env("HOME", *env));
    if (!shlvl ||shlvl[0] == '-')
        i = set_env(env, "SHLVL", "0");
    else if (ft_atoi(shlvl) >= 1000)
    {
        ft_putstr_fd("mish: warning: shell level (", 2);
        shlvl = ft_itoa(ft_atoi(shlvl) + 1);
        ft_putstr_fd(shlvl, 2);
        ft_putstr_fd(") too high, resetting to 1\n", 2);
        i = set_env(env, "SHLVL", "1");
    }
    else
        i = set_env(env, "SHLVL", ft_itoa(ft_atoi(get_env("SHLVL", *env)) + 1)); //increase current shlvl with one
    return (i);
}

int set_env(t_env *env, char *var, char *str)
{
    t_node *tmp;

    tmp = env->start;
    while (tmp)
    {
        if (!my_strcmp(tmp->var, var))
        {
            free(tmp->str);
            tmp->str = str;
            return (0);
        }
        tmp = tmp->next;
    }
    tmp = init_node(ft_strdup(var), str);
    if (!tmp)
        return (1);
    add_to_env(tmp, env);
    return (0);
}

int     in_env(char *var, t_env env)
{
    while (env.start)
    {
        if (ft_strcmp(var, env.start->var))
            return (1);
        env.start = env.start->next;
    }
    return (0);
}

char    *get_env(char *var, t_env env)
{
    while (env.start)
    {
        if (!my_strcmp(var, env.start->var) == 0)
            return (env.start->str);
        env.start = env.start->next;
    }
    return (NULL);
}
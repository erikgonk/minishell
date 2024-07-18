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
#include "env.h"

int set_standard_env(t_env *env, char *shlvl)
{
    int i;

    if (set_env(env, "OLDPWD", NULL, 1))
        return (1);
    if (in_env("PWD", *env) && get_env("PWD", *env))
        env->pwd = ft_strdup(get_env("PWD", *env));
    if (in_env("OLDPWD", *env) && get_env("OLDPWD", *env))
        env->oldpwd = ft_strdup(get_env("OLDPWD", *env)); //setting the oldpwd and pwd in env struct for easy access
    if (!shlvl || shlvl[0] == '-')
        i = set_env(env, "SHLVL", "0", 1);
    else if (ft_atoi(shlvl) >= 1000)
    {
        ft_putstr_fd("mish: warning: shell level (");
        shlvl = ft_itoa(ft_atoi(shlvl) + 1);
        ft_putstr_fd(shlvl);
        ft_putstr_fd(") too high, resetting to 1\n");
        i = set_env(env, "SHLVL", "1", 1);
    }
    else
        i = set_env(env, "SHLVL", ft_itoa(ft_atoi(get_env("SHLVL, *env")) + 1), 1); //increase current shelvl with one
    return (i);
}

int set_env(t_env *env, char *var, char *str, int ow)
{
    t_node *tmp;

    tmp = env->start;
    while (tmp)
    {
        if (!ft_strcmp(tmp->var, var))
        {
            if (ow && tmp->str)
                return (ow_and_str(tmp, str, env));
            else if (ow)
                return (ow_and_nostr(tmp, str, env));
            else
                return (no_ow(tmp, str, env));
        }
        tmp = tmp->next;
    }
    tmp = make_node(ft_strdup(var), str);
    if (add_node_to_env(env, tmp))
        return (-1);
    return (0);
}

int     in_env(char *var, t_env env)
{
    while (env.start)
    {
        if (!ft_strcmp(var, env.start->var))
            return (1);
        env.start = env.start->next;
    }
    return (0);
}

char    *get_env(char *var, t_env env)
{
    while (env.start)
    {
        if (ft_strcmp(var, env.start->var) == 0)
            return (env.start->str);
        env.start = env.start->next;
    }
    return (NULL);
}

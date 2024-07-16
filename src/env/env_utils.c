#include "env.h"

static void update_pwd(t_env *env, char *var, char *str)
{
    if (!ft_strcmp(var, "PWD"))
    {
        if (env->pwd)
            free(env->pwd);
        if (str)
            env->pwd = ft_strdup(str);
        else
            env->pwd = NULL;
    }
    if (!ft_strcmp(var, "OLDPWD"))
    {
        if (env->oldpwd)
            free(env->oldpwd);
        if (str)
            env->oldpwd = ft_strdup(str);
        else
            env->oldpwd = NULL;
    }
}

int  ow_str(t_node *tmp, char *str, t_env *env)
{
    free(tmp->str);
    tmp->str = str;
    update_pwd(env, tmp->var, str);
    return (0);
}

int  ow_nostr(t_node *tmp, char *value, t_env *env)
{
    tmp->str = str;
    update_pwd(env, tmp->var, value);
    return (0);
}

int  no_ow(t_node *tmp, char *str, t_env *env)
{
    char    *cur_env;

    cur_env = ft_strdup(tmp->str);
    if (!cur_env)
        return (1);
    if (tmp->str)
        free(tmp->str);
    tmp->str = ft_strjoin(cur_env, str);
    update_pwd(env, tmp->var, tmp->str);
    free(cur_env);
    free(str);
    return (0);
}
#include "utils.h"

char    *add_shlvl(int lvl)
{
    char    *nbr;
    char    *str;

    nbr = ft_itoa(lvl);
    str = ft_strjoin("SHLVL=", nbr);
    free(nbr);
    return (str);
}

int get_index_shlvl(char *str)
{
    char    *name;

    name = ft_substr(str, 0, ft_strlen(str) - (ft_strlen(ft_strchr(str, '=') + 1)));
    if (ft_strcmp(name, "SHLVL=") == 0)
        return (free(name), 0);
    free(name);
    return (1);
}

int get_shlvl(char *str)
{
    int lvl;

    str = ft_strtrim(str, "SHLVL=");
    lvl = ft_atoi(str);
    lvl++;
    free(str);
    return (lvl);
}

void    increase_shlvl(char **env)
{
    int i;
    int new;

    i = 0;
    if (!env[0])
        return ;
    while (env[i])
    {
        if (get_index_shlvl(env[i]) == 0)
            break ;
        i++;
    }
    new = get_shlvl(env[i]);
    free (env[i]);
    env[i] = add_shlvl(new);
}
#include "minishell.h"

/**
 * Edge case -> if user inputs "cd ~" or "cd ~/"
 * Will check first if it is that command, then 
 * it will check whether the $HOME variable exists
 * in the environment list.
 * If it does not exist, we check whether the saved one (at runtime) exists
 * If that also does not exist, we print an error message because it means 
 * we had no environment to begin with.
*/
static int is_cd_home(t_data *data, char **cmd)
{
    if (cmd && ft_strcmp(cmd[0], "cd") == 0 
        && (ft_strcmp(cmd[1], "~") || ft_strcmp(cmd[1], "~/") == 0))
    {
        if (does_var_exist(data, "$HOME", 0) == 0)
            if (!data->env->homedir)
                return(print_error(data, UNSET_HOME, 0));
    }
    return (1);
}

void    expand(t_data *data, t_cmds *cmds)
{
    t_lex   *tmp;

    cmds->cmd = expand_cmd(data, cmds->cmd);
    is_cd_home(data, cmds->cmd);
    tmp = cmds->redirections;
    while (tmp)
    {
        if (tmp->type != T_HEREDOC)
            tmp->literal = expand_filename(data, tmp->literal);
        tmp = tmp->next;
    }
}

char    **expand_cmd(t_data *data, char **cmd)
{
    int     i;
    char    *expanded;

    i = 0;
    expanded = NULL;
    while (cmd[i])
    {
        expanded = expand_single(data, cmd[i]);
        free(cmd[i]);
        cmd[i] = expanded;
        i++;
    }
    return (cmd);
}

char    *expand_filename(t_data *data, char *filename)
{
    char    *expanded;

    expanded = expand_single(filename);
    free(filename);
    filename = expanded;
    return (filename);
}
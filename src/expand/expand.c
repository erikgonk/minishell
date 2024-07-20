#include "minishell.h"

void    expand(t_data *data, t_cmds *cmds)
{
    t_lex   *tmp;

    cmds->cmd = expand_cmd(data, cmds->cmd);
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
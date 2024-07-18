#include "utils.h"

t_cmds  *cmds_lstnew(char **command)
{
    t_cmds  *new;

    new = (t_cmds *)malloc(sizeof(t_cmds));
    if (!new)
        return (NULL);
    new->cmd = command;
    new->next = NULL;
    return (new);
}

t_cmds  *cmds_lstlast(t_cmds *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    cmds_lstaddback(t_cmds **lst, t_cmds *add)
{
    t_cmds  *tmp;

    if (!lst || !add)
        return ;
    if (*lst == NULL)
        *lst = add;
    else
    {
        tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp = tmp->next;
    }
    return ;
}

void    clean_cmds(t_cmds *cmds)
{
    int     i;
    t_cmds  *tmp;

    while (cmds)
    {
        tmp = cmds->next;
        if (cmds->cmd)
        {
            while (cmds->cmd[++i])
                free(cmds->cmd[i]);
            free(cmds->cmd);
        }
        if (cmds->infile != STDIN_FILENO)
            close(cmds->infile);
        if (cmds->outfile != STDOUT_FILENO)
            close(cmds->outfile);
        if (cmds->redirections)
            free_lex(cmds->redirections);
        free(cmds);
        cmds = tmp;
    }
}
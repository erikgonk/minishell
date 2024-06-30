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
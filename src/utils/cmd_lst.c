#include "../../inc/utils.h"

int     my_strcmp(char *str1, const char *str2)
{
        while (*str1 && *str2 && *str1 == *str2)
        {
                str1++;
                str2++;
        }
        return (*str1 - *str2);
}

t_cmds  *cmds_lstnew(char **command)
{
    t_cmds  *new;

    new = (t_cmds *)malloc(sizeof(t_cmds));
    if (!new)
        return (NULL);
    new->cmd = command;
    new->hdoc = 0;
    new->in = 0;
    new->out = 0;
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

void    cmds_addback(t_cmds **lst, t_cmds *node)
{
    t_cmds	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

void clean_cmds(t_cmds **cmds)
{
    int i;
    t_cmds *tmp;

    if (!cmds || !*cmds)
        return ;
    while (*cmds)
    {
        i = 0;
        tmp = (*cmds)->next;
        if ((*cmds)->cmd)
        {
            while ((*cmds)->cmd[i])
            {
                free((*cmds)->cmd[i]);
                i++;
            }
            free((*cmds)->cmd);
        }
        if ((*cmds)->redirections)
            lex_free(&(*cmds)->redirections);
        free(*cmds);
        *cmds = tmp;
    }
    *cmds = NULL;
}
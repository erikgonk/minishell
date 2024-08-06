#include "../../inc/expander.h"

char *find_var(char *str, t_expander *exp) 
{
    int start;
    int length;
    
    start = exp->pos++;
    if (str[exp->pos] == '?') 
    {
        exp->pos++;
        return ft_strdup("?");
    }
    while (ft_isalnum(str[exp->pos]) || str[exp->pos] == '_') 
        exp->pos++;
    length = exp->pos - start;
    if (length > 0)
        return (ft_substr(str, start, length));
    else
        return (ft_strdup(""));
}

char *expand_var(char *var, t_data *data) 
{
    t_node *tmp;
    
    tmp = data->env->start;
    if (var[0] == '?') 
        return (ft_itoa(data->g_exit));
    while (tmp) 
    {
        if (!ft_strcmp(tmp->var, var) && tmp->str) 
            return (ft_strdup(tmp->str));
        tmp = tmp->next;
    }
    return (ft_strdup(""));
}
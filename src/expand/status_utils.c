#include "../../inc/expander.h"

int get_status(char c, int current) 
{
    if (current == 0) 
    {
        if (c == '\"') 
            return (2);
        if (c == '\'') 
            return (1);
        return (0);
    }
    if (current == 1 && c == '\'') 
        return (0);
    if (current == 2 && c == '\"') 
        return (0);
    return (current);
}

void append_to_finished(t_expander *exp, char *str) 
{
    char *tmp;

    if (exp->finished)
        tmp = ft_strjoin(exp->finished, str);
    else
        tmp = ft_strdup(str);
    if (exp->finished)
        free(exp->finished);
    exp->finished = tmp;
}

void no_quote_exp(char *str, t_expander *exp, t_data *data) 
{
    /*if (str[exp->pos] == '\"' ||str[exp->pos] == '\'')
    exp->pos++;*/
    exp->start = exp->pos;
    while (str[exp->pos] && exp->status == 0) 
    {
        exp->status = get_status(str[exp->pos], exp->status);
        if (str[exp->pos] == '$' ||exp->status != 0) 
            break;
        exp->pos++;
    }
    if (exp->start != exp->pos) 
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start));
        append_to_finished(exp, exp->pre_exp);
        free(exp->pre_exp);
    }
    if (str[exp->pos] == '$') 
    {
        exp->pos++;
        exp->var = find_var(str, exp);
        exp->exp_var = expand_var(exp->var, data);
        append_to_finished(exp, exp->exp_var);
        free(exp->var);
        free(exp->exp_var);
    }
}

void single_quote_exp(char *str, t_expander *exp) 
{
    exp->start = exp->pos;
    if (str[exp->pos] == '\'') 
        exp->start++;
    while (str[exp->pos] && exp->status == 1) 
    {
        exp->pos++;
        exp->status = get_status(str[exp->pos], exp->status);
        if (exp->status != 1) 
            break;
    }
    if (exp->start != exp->pos) 
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start));
        append_to_finished(exp, exp->pre_exp);
        free(exp->pre_exp);
    }
}

void double_quote_exp(char *str, t_expander *exp, t_data *data) 
{
    exp->start = exp->pos;
    if (str[exp->pos] == '\"')
        exp->start++;
    while (str[exp->pos] && exp->status == 2) 
    {        
        exp->pos++;
        exp->status = get_status(str[exp->pos], exp->status);
        if (str[exp->pos] == '$' ||exp->status != 2) 
            break;
    }
    if (exp->start != exp->pos) 
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start));
        append_to_finished(exp, exp->pre_exp);
        free(exp->pre_exp);
    }
    if (str[exp->pos] == '$') 
    {        
        exp->pos++;
        exp->var = find_var(str, exp);
        exp->exp_var = expand_var(exp->var, data);
        append_to_finished(exp, exp->exp_var);
        free(exp->var);
        free(exp->exp_var);
    }
}
#include "../../inc/expander.h"
#include "minishell.h"
/**
 * typedef struct s_expander
{
    char    *pre_and_exp;
    char    *finished;
    char    *exp_var;
    char    *pre_exp;
    char    *var;
    int     pos;
    int     start;
    int     status;
}   t_expander;
*/
void    double_quote_exp(t_data *data, char *str, t_expander *exp)
{
    if (str[pos] == C_DQUOTE)
        exp->start = exp->pos++; //skipping the quote, we don`t want this in the expanded string
    while (str[exp->pos] && exp->status == 2) //iterating until quote is closed
    {
        exp->status = get_status(str[exp->pos]);
        if (str[exp->pos] == '$' || exp->status != 2)
            break ;
        exp->pos++; 
    }
    if (exp->start != exp->pos)
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->pre_exp)
            print_error(data, NULL);
        exp->var = find_var(exp, str, data);
        exp->exp_var = expand_var(exp->var);
        free(exp->var);
        exp->pre_and_exp = ft_strjoin(exp->pre_exp, exp->exp_var);
        free(exp->exp_var);
        free(exp->pre_exp);
        exp->tmp = ft_strjoin(exp->finished, exp->pre_and_exp);
        free(exp->finished);
        exp->finished = ft_strdup(exp->tmp);
    }
}

//no expansion is carried out, but we have to remove the quotes --> [echo]['hello everyone'] should be [echo][hello everyone]
void    single_quote_exp(t_data *data, char *str, t_expander *exp)
{
    if (str[exp->pos] == C_SQUOTE)
        exp->start = exp->pos++;
    while (str[exp->pos] && exp->status == 1)
    {
        exp->pos++;
        exp->status = get_status(str[exp->pos]);
        if (exp->status != 1)
            break ;
    }
    if (exp->start != exp->pos)
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //copying everything inside the single quotes (new string without single quotes)
        if (!exp->pre_exp)
            print_error(data, MALLOC);
        exp->tmp = ft_strjoin(exp->finished, exp->pre_exp);
        exp->finished = ft_strdup(exp->tmp);
        free(exp->tmp);
    }
}

void    no_quote_exp(t_data *data, char *str, t_expander *exp)
{
    exp->start = exp->pos;
    if (str[exp->pos] == C_SQUOTE || str[exp->pos] == C_DQUOTE)
        exp->start = exp->start++;
    while (str[exp->pos] && exp->status == 0) //iterating until quote is closed
    {
        exp->pos++;
        exp->status = get_status(str[exp->pos]);
        if (str[exp->pos] == '$' || exp->status != 0)
            break ; 
    }
    if (exp->start != exp->pos)
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->pre_exp)
            print_error(data, NULL);
        exp->var = find_var(exp, str, data);
        exp->exp_var = expand_var(exp->var);
        free(exp->var);
        exp->pre_and_exp = ft_strjoin(exp->pre_exp, exp->exp_var);
        free(exp->exp_var);
        free(exp->pre_exp);
        exp->tmp = ft_strjoin(exp->finished, exp->pre_and_exp);
        free(exp->finished);
        exp->finished = ft_strdup(exp->tmp);
    }   
}
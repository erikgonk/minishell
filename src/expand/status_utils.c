#include "../../inc/expander.h"
#include "minishell.h"

int     get_status(char c, int current)
{
    if (current == 0)
    {
        if (c == C_DQUOTE)
            return (2);
        if (c == C_SQUOTE)
            return (1);
        else
            return (0);
    }
    if (current == 1)
    {
        if (c == C_SQUOTE)
            return (0);
        else
            return (1);
    }
    if (current == 2)
    {
        if (c == C_DQUOTE)
            return (0);
        else
            return (2);
    }
}

void    no_quote_exp(t_data *data, char *str, t_expander *exp)
{
    while (str[exp->pos] && (str[exp->pos] != C_DQUOTE || str[exp->pos] != C_SQUOTE))
        exp.pos++;
    exp.status = get_status(str[exp->pos], exp->status);
    
}

/**
 * Possibly add a t_exp structure because I am having issues with too many parameters in my function
 * t_exp 
 * {
 *      int status; ---> to know whether we are in double, single or no quote
 *      int pos; ---> to know which position we are in the string
 *      char *result; ---> to store the result of the whole expanded string
 *      char *var; ---> to know which variable to expand when checking environment
 *      char *expanded; ---> the expanded variable (?) don`t know if this is necessary
 * }
*/
char    *expand_single(t_data *data, char *str)
{
    t_expander exp;

    exp.pos = 0;
    exp.finished = NULL;
    exp.start = 0;
    exp.exp_var = NULL;
    exp.pre_and_exp = NULL;
    exp.pre_exp = NULL;
    exp.var = NULL;
    exp.status = get_status(str[exp.pos], 0); //to get the current status (first char)
    while (str[exp.pos])
    {
        if (exp.status == 0)
            no_quote_exp(data, str, &exp);
        if (exp.status == 1)
            single_quote_exp(data, str, &exp);
        if (exp.status == 2)
            double_quote_exp(data, str, &exp);
    }
    return (exp.finished);
}
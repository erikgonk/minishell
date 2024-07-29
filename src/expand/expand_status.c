#include "expander.h"

void    double_quote_exp(t_data *data, char *str, t_expander *exp)
{
    if (str[pos] == C_DQUOTE)
        exp->start = exp->pos++; //skipping the quote, we don`t want this in the expanded string
    while (str[exp->pos] && exp->status == 2) //iterating until quote is closed
    {
        exp->status = get_status(str[exp->pos])
        if (str[exp->pos] == '$')
            break ;
        exp->pos++; 
    }
    if (exp->start != exp->pos)
    {
        exp->sub = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->sub)
            print_error(data, NULL);
        if (check_invalid_chars(str, exp->sub)) //checking whether there are any invalid characters for expansion/if var does not exist
            exp->expanded = ft_strdup(exp->sub); // then just keeping the string unexpanded
        else
            exp->expanded = expand_var(data, exp->sub); //expand the variable if it exists and store in expanded string
        if (!exp->expanded)
            print_error(data, MALLOC);
        free (exp->sub);
        if (exp->finished) // if something is already stored in finished, we free it before storing something else there
            free(exp->finished);
        exp->finished = ft_strjoin(exp->tmp, exp->expanded); //join the tmp string from before with the now newly expanded part of string
        if (!exp->finished)
            print_error(data, MALLOC);
        free(exp->tmp);
        exp->tmp = ft_strdup(exp->finished); //update the tmp variable with the whole finished string ready for next iteration/expansion if we have multiple
        free(exp->expanded);
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
        exp->sub = ft_substr(str, exp->start, (exp->pos - exp->start)); //copying everything inside the single quotes (new string without single quotes)
        if (!exp->sub)
            print_error(data, MALLOC);
        if (exp->finished) //freeing the finished string if exist
            free(exp->finished);
        exp->finished = ft_strjoin(exp->tmp, exp->sub); // updating the finished string by joining the tmp with the new string
        if (!exp->finished)
            print_error(data, MALLOC);
        free(exp->sub);
        free(exp->tmp);
        exp->tmp = ft_strdup(exp->finished); //updating temporary variable to get ready for next expansion
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
        exp->status = get_status(str[exp->pos])
        if (str[exp->pos] == '$')
            break ; 
    }
    if (exp->start != exp->pos)
    {
        exp->sub = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->sub)
            print_error(data, NULL);
        if (check_invalid_chars(str, exp->sub)) //checking whether there are any invalid characters for expansion/if var does not exist
            exp->expanded = ft_strdup(exp->sub); // then just keeping the string unexpanded
        else
            exp->expanded = expand_var(data, exp->sub); //expand the variable if it exists and store in expanded string
        if (!exp->expanded)
            print_error(data, MALLOC);
        free (exp->sub);
        if (exp->finished) // if something is already stored in finished, we free it before storing something else there
            free(exp->finished);
        exp->finished = ft_strjoin(exp->tmp, exp->expanded); //join the tmp string from before with the now newly expanded part of string
        if (!exp->finished)
            print_error(data, MALLOC);
        free(exp->tmp);
        exp->tmp = ft_strdup(exp->finished); //update the tmp variable with the whole finished string ready for next iteration/expansion if we have multiple
        free(exp->expanded);
    }
}
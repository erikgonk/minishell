#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_expander
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

#endif
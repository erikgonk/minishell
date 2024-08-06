#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env			t_env;
typedef struct s_node			t_node;

/*****************env.c*********************/
char    *extract_str(char *envstr);
char    *extract_var(char *envstr);
t_node  *init_node(char *var, char *str);
void    add_to_env(t_node *node, t_env *env);
int     transform_env(t_env *env, char **envp);

/*****************set_env.c*********************/
int     set_standard_env(t_env *env, char *shlvl);
int     set_env(t_env *env, char *var, char *str);
int     in_env(char *var, t_env env);
char    *get_env(char *var, t_env env);

#endif
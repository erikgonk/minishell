#include "./inc/expander.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct s_node
{
    char    *var;
    char    *str;
    struct s_node   *next;
}   t_node;

typedef struct s_env
{
    t_node      *start;
    t_node      *end;
    char        *pwd;
    char        *oldpwd;
    char        *shlvl;
    char        *homedir; //for cd ~
}   t_env;

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

static int	count(int n)
{
	int		digits;

	digits = 0;
	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		digits++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static int	exponent(int n)
{
	int		exp;
	int		digits;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (1000000000);
	digits = count(n);
	if (n < 0)
	{
		n = -n;
		digits--;
	}
	exp = 1;
	while (--digits)
	{
		exp *= 10;
	}
	return (exp);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			i;
	long int		exp;
	long int		copy;

	i = 0;
	exp = exponent(n);
	copy = (long int)n;
	str = malloc(sizeof(char) * (count(n) + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		copy = -copy;
		str[i++] = '-';
	}
	while (exp > 0)
	{
		str[i++] = (copy / exp) + 48;
		copy = copy % exp;
		exp /= 10;
	}
	str[i] = '\0';
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				res;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	res *= sign;
	return (res);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char		*c;
	char		*c_s1;
	size_t		i;

	c_s1 = (char *)s1;
	c = (char *)malloc(ft_strlen(c_s1) + 1);
	if (!c)
		return (0);
	i = 0;
	while (c_s1[i] != '\0')
	{
		c[i] = c_s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	if (!(s1 && s2))
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > len_s)
		return (ft_strdup(""));
	len_s -= start;
	if (len_s < len)
		len = len_s;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int     get_status(char c, int current)
{
    if (current == 0)
    {
        if (c == '\"')
            return (2);
        if (c == '\'')
            return (1);
        else
            return (0);
    }
    if (current == 1)
    {
        if (c == '\'')
            return (0);
        else
            return (1);
    }
    if (current == 2)
    {
        if (c == '\"')
            return (0);
        else
            return (2);
    }
}

char    *expand_var(char *var, t_env *env)
{
    t_node  *tmp;

    tmp = env->start;
    while (tmp)
    {
        if (!ft_strcmp(tmp->var, var) && tmp->str)
            return(ft_strdup(tmp->str));
        tmp = tmp->next;
    }
    return (ft_strdup(""));
}

char    *find_var(char  *str, t_expander *exp)
{
    int     start;
    int     length;

    exp->pos++;
    start = exp->pos;
    while (ft_isalnum(str[exp->pos]) || str[exp->pos] == '_')
        exp->pos++;
    length = exp->pos - start;
    if (length <= 0)
        return (NULL);
    return(ft_substr(str, start, length));
}

void    double_quote_exp(char *str, t_expander *exp, t_env *env)
{
    char    *tmp;

    if (str[exp->pos] == '\"')
        exp->pos++;
    exp->start = exp->pos; //skipping the quote, we don`t want this in the expanded string
    while (str[exp->pos] && exp->status == 2) //iterating until quote is closed
    {
        exp->status = get_status(str[exp->pos], 2);
        if (str[exp->pos] == '$' || exp->status != 2)
            break ;
        exp->pos++; 
    }
    if (str[exp->pos] == '$')
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->pre_exp)
            printf("error malloc");
        exp->var = find_var(str, exp);
        exp->exp_var = expand_var(exp->var, env);
        if (!exp->exp_var)
            exp->exp_var = ft_strdup("");
        free(exp->var);
        exp->pre_and_exp = ft_strjoin(exp->pre_exp, exp->exp_var);
        free(exp->exp_var);
        free(exp->pre_exp);
        if (!exp->finished)
            exp->finished = ft_strdup("");
        tmp = ft_strjoin(exp->finished, exp->pre_and_exp);
        free(exp->finished);
        free(exp->pre_and_exp);
        exp->finished = tmp;
    }
}

//no expansion is carried out, but we have to remove the quotes --> [echo]['hello everyone'] should be [echo][hello everyone]
void    single_quote_exp(char *str, t_expander *exp)
{
    char    *tmp;

    if (str[exp->pos] == '\'')
        exp->pos++;
    exp->start = exp->pos;
    while (str[exp->pos] && exp->status == 1)
    {
        exp->pos++;
        exp->status = get_status(str[exp->pos], 1);
        if (exp->status != 1)
            break ;
    }
    if (exp->start != exp->pos)
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //copying everything inside the single quotes (new string without single quotes)
        if (!exp->pre_exp)
            printf("error malloc");
        if (!exp->finished)
            exp->finished = ft_strdup("");
        tmp = ft_strjoin(exp->finished, exp->pre_exp);
        exp->finished = ft_strdup(tmp);
        free(tmp);
    }
}

void    no_quote_exp(char *str, t_expander *exp, t_env *env)
{
    char    *tmp;

    exp->start = exp->pos;
    if (str[exp->pos] == '\'' || str[exp->pos] == '\"')
        exp->start++;
    while (str[exp->pos] && exp->status == 0) //iterating until quote is closed
    {
        exp->status = get_status(str[exp->pos], 0);
        if (str[exp->pos] == '$' || exp->status != 0)
            break ;
        exp->pos++;
    }
    if (str[exp->pos] == '$')
    {
        exp->pre_exp = ft_substr(str, exp->start, (exp->pos - exp->start)); //save string until the '$' symbol
        if (!exp->pre_exp)
            printf("error malloc");
        exp->var = find_var(str, exp);
        exp->exp_var = expand_var(exp->var, env);
        if (!exp->exp_var)
            exp->exp_var = ft_strdup("");
        free(exp->var);
        exp->pre_and_exp = ft_strjoin(exp->pre_exp, exp->exp_var);
        free(exp->exp_var);
        free(exp->pre_exp);
        if (!exp->finished)
            exp->finished = ft_strdup("");
        tmp = ft_strjoin(exp->finished, exp->pre_and_exp);
        free(exp->finished);
        free(exp->pre_and_exp);
        exp->finished = tmp;
    }   
}

char    *expand_single(char *str, t_env *env)
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
    while (str[exp.pos] != '\0')
    {
        if (exp.status == 0)
            no_quote_exp(str, &exp, env);
        if (exp.status == 1)
            single_quote_exp(str, &exp);
        if (exp.status == 2)
            double_quote_exp(str, &exp, env);
    }
    return (exp.finished);
}

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*((unsigned char *)s++) = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == 0)
		return (0);
	ft_bzero(str, count * size);
	return (str);
}


char    *extract_str(char *envstr)
{
    int     i;
    int     start;
    int     end;
    char    *str;

    i = 0;
    while (envstr[i])
    {
        if (envstr[i] == '=' && envstr[i + 1] != ' ') //and other whitespace?
        {
            start = i + 1;
            end = ft_strlen(envstr);
            str = ft_substr(envstr, start, end);
            if (!str)
                return (NULL);
            return (str);
        }
        i++;
    }
    return (NULL);
}

char    *extract_var(char *envstr)
{
    int     i;
    int     start;
    int     end;
    char    *var;

    i = 0;
    start = 0;
    while (envstr[i])
    {
        if (envstr[i + 1] == '=')
        {
            end = i + 1;
            var = ft_substr(envstr, start, end);
            if (!var)
                return (NULL);
            return (var);
        }
        i++;
    }
    return (NULL);
}

t_node  *init_node(char *var, char *str)
{
    t_node  *new;

    new = ft_calloc(1, sizeof(t_node));
    if (!new)
        return (NULL);
    new->var = var;
    new->str = str;
    new->next = NULL;
    return (new);
}

void add_to_env(t_node *node, t_env *env)
{
    if (!env->start)
    {
        env->start = node;
        env->end = node;
    }
    else
    {
        env->end->next = node;
        env->end = node;
    }
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int set_env(t_env *env, char *var, char *str)
{
    t_node *tmp;

    tmp = env->start;
    while (tmp)
    {
        if (!ft_strcmp(tmp->var, var))
        {
            free(tmp->str);
            tmp->str = str;
            return (0);
        }
        tmp = tmp->next;
    }
    tmp = init_node(ft_strdup(var), str);
    if (!tmp)
        return (1);
    add_to_env(tmp, env);
    return (0);
}

int     in_env(char *var, t_env env)
{
    while (env.start)
    {
        if (!ft_strcmp(var, env.start->var))
            return (1);
        env.start = env.start->next;
    }
    return (0);
}

char    *get_env(char *var, t_env env)
{
    while (env.start)
    {
        if (ft_strcmp(var, env.start->var) == 0)
            return (env.start->str);
        env.start = env.start->next;
    }
    return (NULL);
}

int set_standard_env(t_env *env, char *shlvl)
{
    int i;

    i = 1;
    if (set_env(env, "OLDPWD", NULL))
        return (i);
    if (in_env("PWD", *env) && get_env("PWD", *env))
        env->pwd = ft_strdup(get_env("PWD", *env));
    if (in_env("OLDPWD", *env) && get_env("OLDPWD", *env))
        env->oldpwd = ft_strdup(get_env("OLDPWD", *env));
    if (in_env("HOME", *env) && get_env("HOME", *env))
        env->homedir = ft_strdup(get_env("HOME", *env));
    if (!shlvl ||shlvl[0] == '-')
        i = set_env(env, "SHLVL", "0");
    else if (ft_atoi(shlvl) >= 1000)
    {
        ft_putstr_fd("mish: warning: shell level (", 2);
        shlvl = ft_itoa(ft_atoi(shlvl) + 1);
        ft_putstr_fd(shlvl, 2);
        ft_putstr_fd(") too high, resetting to 1\n", 2);
        i = set_env(env, "SHLVL", "1");
    }
    else
        i = set_env(env, "SHLVL", ft_itoa(ft_atoi(get_env("SHLVL", *env)) + 1)); //increase current shlvl with one
    return (i);
}

int    transform_env(t_env *env, char **envp)
{
    t_node  *node;
    int     i;
    char    *var;
    char    *str;

    i = 0;
    while (envp[i])
    {
        var = extract_var(envp[i]);
        str = extract_str(envp[i]);
        node = init_node(var, str);
        add_to_env(node, env);
        i++;
    }
    if (set_standard_env(env, get_env("SHLVL", *env)))
		return (1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_env   env;
    char    *expanded;

    env.start = NULL;
    env.end = NULL;
    env.homedir = NULL;
    env.oldpwd = NULL;
    env.pwd = NULL;
    transform_env(&env, envp);
    expanded = expand_single("\"'$HELLO' $USER\"", &env);
    /*t_node *lst;
    lst = env.start;
    while (lst)
    {
        printf("%s=%s\n", lst->var, lst->str);
        lst = lst->next;
    }
    printf("pwd=%s, oldpwd=%s, homedir=%s\n", env.pwd, env.oldpwd, env.homedir);*/
    printf("Expansion: %s", expanded);
    return (0);
}

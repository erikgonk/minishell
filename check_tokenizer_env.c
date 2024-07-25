# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
// malloc, free, exit
# include <stdlib.h>
// open, unlink
# include <fcntl.h>
// waitpid, wait
# include <sys/wait.h>
# include <string.h>
// strerror 
// perror
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "mish> "
# define C_LESS '<'
# define C_GREAT '>'
# define C_PIPE '|'
# define C_SQUOTE '\''
# define C_DQUOTE '"'

/*-----------------Enums------------------*/
typedef enum e_token
{
	T_PIPE = 1,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_WORD,
}   e_token;

typedef enum e_builtin
{
    PWD = 1,
    ECHO,
    CD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    NO_BUILTIN,
}   e_builtin;

/*--------------Structures----------------*/
typedef struct s_lex
{
	enum e_token	type; //type of token
	char			*literal; //the string literal (eg. "cat -e")
	int				index; //position in the linked list
	struct s_lex	*next;
}	t_lex;

typedef struct s_data
{
    char        *input; // users input string
    t_lex       *lexer; // pointer to the linked list of tokens
    int         hdoc_count; // How many heredocs are present in the input
    int         *pid; // Pointer to array of the pids
    int         g_exit; // "global" return error number
    int         printed_error;
    int         pipes; // NUmber of pipes present to know for how many child processes needed
}   t_data;

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
    char        *homedir; //for cd ~
}   t_env;

t_lex	*tokenizer(char *input, t_data *data);
int     token_length(char *input);
void    add_index(t_lex *tokens);
void    free_tokens(t_lex *tokens);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length, t_data *data);
int  find_type(char *literal);
void    mini_loop(t_data *data);
int set_env(t_env *env, char *var, char *str, int ow);
char    *get_env(char *var, t_env env);


void    ft_print_env(t_node *env)
{
	while (env)
	{
		if (env->var && env->str)
			printf("%s=%s\n", env->var, env->str);
		env = env->next;
	}
}

int	ft_env(t_env *env)
{
	if (!env->start || !env->start->var || !env->start->str)
	{
		printf("env: not found");
		return (1);
	}
	ft_print_env(env->start);
	return (0);
}



/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
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

char	*ft_strdup(char *s1)
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

static void update_pwd(t_env *env, char *var, char *str)
{
    if (!ft_strcmp(var, "PWD"))
    {
        if (env->pwd)
            free(env->pwd);
        if (str)
            env->pwd = ft_strdup(str);
        else
            env->pwd = NULL;
    }
    if (!ft_strcmp(var, "OLDPWD"))
    {
        if (env->oldpwd)
            free(env->oldpwd);
        if (str)
            env->oldpwd = ft_strdup(str);
        else
            env->oldpwd = NULL;
    }
}

int  ow_and_str(t_node *tmp, char *str, t_env *env)
{
    free(tmp->str);
    tmp->str = str;
    update_pwd(env, tmp->var, str);
    return (0);
}

int  ow_and_nostr(t_node *tmp, char *str, t_env *env)
{
    tmp->str = str;
    update_pwd(env, tmp->var, str);
    return (0);
}

int  no_ow(t_node *tmp, char *str, t_env *env)
{
    char    *cur_env;

    cur_env = ft_strdup(tmp->str);
    if (!cur_env)
        return (1);
    if (tmp->str)
        free(tmp->str);
    tmp->str = ft_strjoin(cur_env, str);
    update_pwd(env, tmp->var, tmp->str);
    free(cur_env);
    free(str);
    return (0);
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
    end = i;
    var = ft_substr(envstr, start, end);
    return (var);
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

int set_env(t_env *env, char *var, char *str, int ow)
{
    t_node *tmp;

    tmp = env->start;
    while (tmp)
    {
        if (!ft_strcmp(tmp->var, var))
        {
            if (ow && tmp->str)
                return (ow_and_str(tmp, str, env));
            else if (ow)
                return (ow_and_nostr(tmp, str, env));
            else
                return (no_ow(tmp, str, env));
        }
        tmp = tmp->next;
    }
    tmp = init_node(ft_strdup(var), str);
    if (!tmp)
        return (-1);
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

    if (set_env(env, "OLDPWD", NULL, 1))
        return (1);
    if (in_env("PWD", *env) && get_env("PWD", *env))
        env->pwd = ft_strdup(get_env("PWD", *env));
    if (in_env("OLDPWD", *env) && get_env("OLDPWD", *env))
        env->oldpwd = ft_strdup(get_env("OLDPWD", *env));
    /*if (in_env("HOME", *env) && get_env("HOME", *env))
        env->homedir = ft_strdup(get_env("HOME", *env));*/
    if (!shlvl ||shlvl[0] == '-')
        i = set_env(env, "SHLVL", "0", 1);
    else if (ft_atoi(shlvl) >= 1000)
    {
        ft_putstr_fd("mish: warning: shell level (", 2);
        shlvl = ft_itoa(ft_atoi(shlvl) + 1);
        ft_putstr_fd(shlvl, 2);
        ft_putstr_fd(") too high, resetting to 1\n", 2);
        i = set_env(env, "SHLVL", "1", 1);
    }
    else
        i = set_env(env, "SHLVL", ft_itoa(ft_atoi(get_env("SHLVL", *env)) + 1), 1); //increase current shlvl with one
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

void    add_index(t_lex *tokens)
{
    int i;

    i = 0;
    while (tokens)
    {
        tokens->index = i;
        tokens = tokens->next;
        i++;
    }
}

static int quote_length(char *str, char quote_char)
{
    int length = 1;
    str++;
    while (*str)
    {
        length++;
        if (*str == quote_char)
            return (length);
        str++;
    }
    return (length);
}

int token_length(char *input)
{
    int length = 0;
    int add = 1;

    if ((input[0] == C_LESS && input[1] == C_LESS) || (input[0] == C_GREAT && input[1] == C_GREAT))
        return 2;
    else if (input[0] == C_PIPE || input[0] == C_GREAT || input[0] == C_LESS)
        return 1;
    while (input[length] && input[length] != C_PIPE && input[length] != C_LESS && input[length] != C_GREAT && input[length] != ' ')
    {
        if (input[length] == C_SQUOTE || input[length] == C_DQUOTE)
            add = quote_length(input + length, input[length]);
        else
            add = 1;
        length += add;
    }

    return length;
}

int syntax_check(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == ';')
        {
            printf("mish: illegal symbol ';': not in eval sheet\n");
            return(1);
        }
        else if (input[i] == '\\')
        {
            printf("mish: illegal symbol '\\': not in eval sheet\n");
            return(1);
        }
        else
            i++;
    }
    return (0);
}

int lex_lstlen(t_lex *tokens)
{
    int i = 0;
    while (tokens)
    {
        i++;
        tokens = tokens->next;
    }
    return (i);
}

int is_hdoc_present(t_lex *tokens)
{
    if (lex_lstlen(tokens) > 1)
    {
        while (tokens)
        {
            if (tokens->type == T_HEREDOC)
                return (1);
            tokens = tokens->next;
        }
    }
    return (0);
}

void    print_error(int type, t_data *data)
{
    if (!data->printed_error)
    {
        if (type == T_PIPE)
            printf("Syntax error near unexpected token '|'\n");
        if (type == T_REDIR_IN)
            printf("Syntax error near unexpected token '<'\n");
        if (type == T_HEREDOC)
            printf("Syntax error near unexpected token '<<'\n");
        if (type == T_REDIR_OUT)
            printf("Syntax error near unexpected token '>'\n");
        if (type == T_APPEND)
            printf("Syntax error near unexpected token '>>'\n");
        if (type == 10)
            printf("Syntax error near unexpected token 'newline'\n");
        data->printed_error = 1;
    }
    return ;
}

int  find_next(char *literal, int i)
{
    if ((literal[i] == C_LESS && literal[i + 1] == C_LESS))
        return (T_HEREDOC);
    if ((literal[i] == C_GREAT && literal[i + 1] == C_GREAT))
        return (T_APPEND);
    if (literal[i] == C_PIPE)
        return (T_PIPE);
    if (literal[i] == C_LESS)
        return (T_REDIR_IN);
    if (literal[i] == C_GREAT)
        return (T_REDIR_OUT);
    return(10);
}

int check_syntax_and_hdoc(t_data *data, t_lex *tokens, char *input, t_lex *new, int i)
{
	if (input[i] == ' ' || (input[i] >= 8 && input[i] <= 13))
        i++;
	if (input[i] == '>' || input[i] == '<' || input[i] == '|' || !input[i])
	{
		if (is_hdoc_present(tokens))
			new->index = -1; //raising flag for spesific error
        print_error(find_next(input, i), data);
        data->g_exit = 2;
	}
    return (0);
}

static t_lex *make_token(int length, char *input, t_lex *tokens, t_data *data)
{
    int i;
    t_lex *new;

    i = 0;
    new = malloc(sizeof(t_lex));
    if (!new)
        return (NULL);
    new->index = 0;
    new->literal = (char *)malloc(sizeof(char) * (length + 1));
    if (!new->literal)
    {
        free(new);
        return (NULL);
    }
    while (i < length)
    {
        new->literal[i] = input[i];
        i++;
    }
    new->literal[i] = '\0';
    new->next = NULL;
    new->type = find_type(new->literal);
    if (new->type == T_APPEND || new->type == T_REDIR_IN || new->type == T_HEREDOC || new->type == T_REDIR_OUT || new->type == T_PIPE)
        check_syntax_and_hdoc(data, tokens, input, new, i);
    return (new);
}

void    lex_free(t_lex **lst)
{
    t_lex *tmp;

    if (!*lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        if ((*lst)->literal)
            free((*lst)->literal);
        free(*lst);
        (*lst) = tmp;
    }
    *lst = NULL;
}

t_lex *fill_tokens(t_lex *tokens, char *input, int length, t_data *data)
{
    t_lex *last;
    t_lex *new;

    new = make_token(length, input, tokens, data);
    if (!new)
        return (NULL);
    if (tokens == NULL)
        tokens = new;
    else
    {
        last = tokens;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
    }
    return (tokens);
}

void    lex_clearone(t_lex **lst)
{
    if ((*lst)->literal)
    {
        free((*lst)->literal);
        (*lst)->literal = NULL;
    }
    free(*lst);
    *lst = NULL;
}

void    lex_delfirst(t_lex **lst)
{
    t_lex   *tmp;

    tmp = *lst;
    *lst = tmp->next;
    lex_clearone(&tmp);
}

void    lex_delone(t_lex **lst, int del)
{
    t_lex   *node;
    t_lex   *prev;

    node = *lst;
    prev = NULL;
    if (node && node->index == del)
    {
        lex_delfirst(lst);
        return ;
    }
    while (node && node->index != del)
    {
        prev = node;
        node = node->next;
    }
    if (node)
    {
        if (prev)
            prev->next = node->next;
        lex_clearone(&node);
    }
}

int  find_type(char *literal)
{
    if ((literal[0] == C_LESS && literal[1] == C_LESS))
        return (T_HEREDOC);
    if ((literal[0] == C_GREAT && literal[1] == C_GREAT))
        return (T_APPEND);
    if (literal[0] == C_PIPE)
        return (T_PIPE);
    if (literal[0] == C_LESS)
        return (T_REDIR_IN);
    if (literal[0] == C_GREAT)
        return (T_REDIR_OUT);
    return (T_WORD);
}

t_lex   *lex_lstlast(t_lex *tokens)
{
    while (tokens->next)
        tokens = tokens->next;
    return (tokens);
}

t_lex	*tokenizer(char *input, t_data *data)
{
	t_lex	*tokens;
	int		length;
    t_lex   *last;

	length = 0;
	tokens = NULL;
	while (*input)
	{
		if (*input == ' ' || (*input >= 8 && *input <= 13))
			input++;
		else
		{
			length = token_length(input);
			tokens = fill_tokens(tokens, input, length, data);
            last = lex_lstlast(tokens);
            if (last->index == -1)
            {
                lex_delone(&tokens, -1);
                break ;
            }
			input += length;
		}
	}
	add_index(tokens);
	return(tokens);
}

int check_redirs(t_lex **lst, t_data *data)
{
    if (((*lst)->type >= T_REDIR_IN && (*lst)->type <= T_APPEND) && (!(*lst)->next ||(*lst)->next->type != T_WORD))
    {
        data->g_exit = 2;
        return (0);
    }
    return (1);
}

int check_pipes(t_lex **lst, t_data *data)
{
    if ((*lst)->type == T_PIPE && ((!(*lst)->next) ||((*lst)->next->type != T_WORD && !((*lst)->next->type >= T_REDIR_IN && (*lst)->next->type <= T_APPEND))))
    {
        data->g_exit = 2;
        return (0);
    }
    return (1);
}

int    check_tokens(t_data *data, t_lex **lst)
{
    if (!(*lst))
        return (0);
    if ((*lst)->type == T_PIPE)
    {
        data->g_exit = 2;
        return (0);
    }
    while (*lst)
    {
        if (!check_redirs(lst, data) ||!check_pipes(lst, data))
            return (0);
        lst = &(*lst)->next;
    }
    return (1);
}

int	change_flag(int flag)
{
	if (flag == 0)
		return (1);
	else
		return (0);
}

int	quotes(char *input, int *i, int flag, char c)
{
	if (input[*i] == c)
	{
		flag = change_flag(flag);
		(*i)++;
		while (input[*i] && input[*i] != c)
			(*i)++;
		if (input[*i] == c)
		{
			flag = change_flag(flag);
			(*i)++;
		}
	}
	return (flag);
}

int	quote_checker(char *str)
{
	int	single_flag;
	int	double_flag;
	int	i;
	int	j;

	double_flag = 0;
	single_flag = 0;
	i = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		j = i;
		double_flag = quotes(str, &i, double_flag, '\"');
		single_flag = quotes(str, &i, single_flag, '\'');
		if (i == j)
			i++;
	}
	if (double_flag || single_flag)
		return(1);
    return (0);
}

int	arg_count(char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

/**
 * Just some checks to make sure the program does not crash
 * if the user decides to be annoying and input too many 
 * arguments or use open quotes.
*/
int input_check(char *input, t_data *data)
{
    if (quote_checker(input))
    {
        printf("minish: syntax error: open quotes\n");
        data->g_exit = 2;
        return (1);
    }
    if (syntax_check(input))
    {
        data->g_exit = 1;
        return (1);
    }
    if (arg_count(input, ' ') > 100) //idk how many arguments should be limit here 
    {
        printf("mish: don't be crazy: too many arguments\n");
        data->g_exit = 1;
        return (1);
    }
    if (ft_strlen(input) > 4096)
    {
        printf("mish: don't be annoying: the prompt is too long\n");
        data->g_exit = 1;
        return (1);
    }
    return (0);
}

int	init_minishell(t_env *env, t_data *data, char **envp)
{
    /*if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);*/
	data->g_exit = 0;
    data->lexer = NULL;
    data->pipes = 0;
    data->hdoc_count = 0;
    data->printed_error = 0;
    env->start = NULL;
    env->end = NULL;
    env->homedir = NULL;
    env->oldpwd = NULL;
    env->pwd = NULL;
    if (transform_env(env, envp)) //should not exit if environment is not found, shell should still be working (?)
		exit(1);
    ft_print_env(env->start);
	return (0);
}

char    *clean_input(char *input)
{
    if (input)
        free(input);
    return (NULL);
}

char    *get_input(t_data *data)
{
    data->input = readline("Mish> ");
    if (data->input == NULL)
    {
        if (isatty(STDIN_FILENO))
            printf("exit\n");
        exit(data->g_exit);
    }
    else if (data->input)
    {
        add_history(data->input);
        if (input_check(data->input, data))
            data->input[0] = '\0';
    }
    return (data->input);
}

void    mini_loop(t_data *data)
{
    char    *input;

    input = NULL;
    while (1)
    {
        data->printed_error = 0;
        lex_free(&data->lexer);
        /*clean_cmds(data->cmds);*/
        input = clean_input(input);
        input = get_input(data);
        if (input[0] == '\0')
        {
            printf("%i\n", data->g_exit);
            continue ;
        }
        data->lexer = tokenizer(input, data);
                if (!data->lexer)
            continue ;
        check_tokens(data, &data->lexer);
        printf("%i\n", data->g_exit);
    }
    rl_clear_history();
}

void    clean_shell(t_data *data)
{
    if (data->lexer)
        lex_free(&data->lexer);
    if (data->input)
        clean_input(data->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    t_env   env;

    if (argc != 1 ||argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }

	init_minishell(&env, &data, envp);
	mini_loop(&data);
	/*clean_shell(&env, &data);*/
	return (0);
}
/*
int main()
{
    t_lex *tokens;
    t_data data;

    data.g_exit = 0;
    tokens = tokenizer("<< ls | cat -e file > outfile |", &data);
    check_tokens(&data, &tokens);
    while (tokens)
    {
        printf("%i ", tokens->index);
        printf("%s ", tokens->literal);
        printf("%i ", tokens->type);
        printf("error status: %i", data.g_exit);
        printf("\n");
        tokens = tokens->next;
    }
    return (0);
}*/


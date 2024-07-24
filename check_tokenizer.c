# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
// malloc, free, exit
# include <stdlib.h>
// open, unlink
# include <fcntl.h>
// waitpid, wait
# include <sys/wait.h>
// strerror 
# include <string.h>
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

t_lex	*tokenizer(char *input, t_data *data);
int     token_length(char *input);
void    add_index(t_lex *tokens);
void    free_tokens(t_lex *tokens);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length, t_data *data);
int  find_type(char *literal);
void    mini_loop(t_data *data);


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

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
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

int	init_minishell(t_data *data, char **envp)
{
    /*if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);*/
	data->g_exit = 0;
    data->lexer = NULL;
    data->pipes = 0;
    data->hdoc_count = 0;
    data->printed_error = 0;
    /*env->start = NULL;
    env->end = NULL;
    env->homedir = NULL;
    env->old_pwd = NULL;
    env->pwd = NULL;
    if (transform_env(env, envp)) //should not exit if environment is not found, shell should still be working (?)
		exit(1);*/
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

    if (argc != 1 ||argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
	init_minishell(&data, envp);
	mini_loop(&data);
	/*clean_shell(&env, &data); -> not including may cause some leaks*/
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


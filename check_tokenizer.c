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
    int         pipes; // NUmber of pipes present to know for how many child processes needed
}   t_data;

t_lex	*tokenizer(char *input, t_data *data);
int     token_length(char *input);
void    add_index(t_lex *tokens);
void    free_tokens(t_lex *tokens);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length, t_data *data);
int  find_type(char *literal);


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

int is_hdoc_present(t_lex *tokens)
{
    while (tokens)
    {
        if (tokens->type == T_HEREDOC)
            return (1);
        tokens = tokens->next;
    }
    return (0);
}

void    print_error(int type)
{
    if (type == 1)
        printf("Syntax error near unexpected token '>'");
    printf("Syntax error near unexpected token '>'\n");
    return ;
}

int check_syntax_and_hdoc(t_data *data, t_lex *tokens, char *input, t_lex *new)
{
    int i;

    i = 0;
	if (input[i] == ' ' || (input[i] >= 8 && input[i] <= 13))
        i++;
	if (input[i] == '>' || input[i] == '<' || input[i] == '|' || !input[i])
	{
		if (is_hdoc_present(tokens))
		{
			data->g_exit = 2;
			print_error(new->type);
			new->index = -1; //raising flag to check whether we encountered this spesific error
		}
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
        check_syntax_and_hdoc(data, tokens, input, new);
    return (new);
}

void    lex_free(t_lex *lst)
{
    t_lex *tmp;

    if (!lst)
        return ;
    while (lst)
    {
        free(lst->literal);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
    return ;
}

t_lex *fill_tokens(t_lex *tokens, char *input, int length, t_data *data)
{
    t_lex *last;
    t_lex *new;

    new = make_token(length, input, tokens, data);
    if (!new)
    {
        if (tokens)
            lex_free(tokens);
        return (NULL);
    }
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

int main()
{
    t_lex *tokens;
    t_data data;

    data.g_exit = 0;
    tokens = tokenizer("<< here > > << hey>", &data);
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
}


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

t_lex	*tokenizer(char *input);
int     token_length(char *input);
void    add_index(t_lex *tokens);
void    free_tokens(t_lex *tokens);
t_lex   *fill_tokens(t_lex *tokens, char *input, int length);
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

static t_lex *make_token(int length, char *input)
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

t_lex *fill_tokens(t_lex *tokens, char *input, int length)
{
    t_lex *last;
    t_lex *new;

    new = make_token(length, input);
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

t_lex	*tokenizer(char *input)
{
	t_lex	*tokens;
	int		length;

	length = 0;
	tokens = NULL;
	while (*input)
	{
		if (*input == ' ' || (*input >= 8 && *input <= 13))
			input++;
		else
		{
			length = token_length(input);
			tokens = fill_tokens(tokens, input, length);
			input += length;
		}
	}
	add_index(tokens);
	return(tokens);
}

int main()
{
    t_lex *tokens;

    tokens = tokenizer("ls > out | cat -e << here");
    while (tokens)
    {
        printf("%i ", tokens->index);
        printf("%s ", tokens->literal);
        printf("%i ", tokens->type);
        printf("\n");
        tokens = tokens->next;
    }
    return (0);
}


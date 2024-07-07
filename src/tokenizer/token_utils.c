#include "tokenizer.h"

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




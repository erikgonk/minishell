#include "tokenizer.h"

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
#include "tokenizer.h"

int pre_parser_checks(t_data *data)
{
    if (quote_checker(data->input))
    {
        ft_putstr_fd("minishell: open quotes\n", 2);
        return (258);
    }
    if (arg_count(data->input, 32) > MAXARGS)
    {
        ft_putstr_fd("minishell: don't be crazy: too many arguments\n", 2);
        return (1);
    }
    if (ft_strlen(data->input) > 4096)
    {
        ft_putstr_fd("minishell: don't be annoying: the prompt is too long\n", 2);
        return (1);
    }
    return (0);
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
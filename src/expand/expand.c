/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:17:15 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/12 11:28:28 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/expander.h"

char	*expand_single(char *str, t_data *data)
{
	t_expander	exp;

	exp.pos = 0;
	exp.finished = NULL;
	exp.start = 0;
	exp.exp_var = NULL;
	exp.pre_and_exp = NULL;
	exp.pre_exp = NULL;
	exp.var = NULL;
	exp.status = get_status(str[exp.pos], 0);
	while (str[exp.pos] != '\0')
	{
		if (exp.status == 0)
			no_quote_exp(str, &exp, data);
		if (exp.status == 1)
			single_quote_exp(str, &exp);
		if (exp.status == 2)
			double_quote_exp(str, &exp, data);
		get_status(str[exp.pos], exp.status);
	}
	return (exp.finished);
}

void	expand(t_data *data, t_cmds *cmds)
{
	t_lex	*tmp;

	if (cmds->cmd)
		cmds->cmd = expand_cmd(cmds->cmd, data);
	tmp = cmds->redirections;
	while (tmp)
	{
		if (tmp->type != T_HEREDOC)
			tmp->literal = expand_filename(tmp->literal, data);
		tmp = tmp->next;
	}
}

char	**expand_cmd(char **cmd, t_data *data)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd[i])
	{
		if (!my_strcmp("\"\"", cmd[i]) || !my_strcmp("\'\'", cmd[i]))
		{
			free(cmd[i]);
			cmd[i] = ft_strdup("");
		}
		else
		{
			expanded = expand_single(cmd[i], data);
			free(cmd[i]);
			cmd[i] = expanded;
		}
		i++;
	}
	return (cmd);
}

char	*expand_filename(char *filename, t_data *data)
{
	char	*expanded;

	expanded = expand_single(filename, data);
	free(filename);
	return (expanded);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:29:51 by vaunevik          #+#    #+#             */
/*   Updated: 2024/08/14 12:29:54 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_data		t_data;
typedef struct s_expander	t_expander;

/**************expand.c******************/
char						*expand_filename(char *filename, t_data *data);
char						**expand_cmd(char **cmd, t_data *data);
void						expand(t_data *data, t_cmds *cmds);
char						*expand_single(char *str, t_data *data);

/************status_utils.c***************/
int							get_status(char c, int current);
void						append_to_finished(t_expander *exp, char *str);
void						no_quote_exp(char *str, t_expander *exp,
								t_data *data);
void						single_quote_exp(char *str, t_expander *exp);
void						double_quote_exp(char *str, t_expander *exp,
								t_data *data);

/***************var_expand.c*************/
char						*find_var(char *str, t_expander *exp);
char						*expand_var(char *var, t_data *data);

#endif

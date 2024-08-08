/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/08 10:09:07 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define F_NONE 0
# define F_ADD 1
# define F_CREATE 2

// CD
int					ft_cd(t_exec *exec);

// ECHO
int					ft_echo(t_exec *exec);

// ENV
int					ft_env(t_exec *exec);
void				ft_print_env(t_node *env);

// EXPORT
int					ft_export(t_exec *exec);
// EXPORT_utils1 (for export alone)
int					ft_print_export(t_exec *exec);
int					ft_small_char(char **lst, int i, int j, int k);
// EXPORT_utils2 (general)
int					ft_find_char(char *str, char c);
int					ft_count_lst_elems(t_node *lst);
char				**ft_sort_lst_exp(char **lst, int i, int j, int pos);
// EXPORT_utils3 (export alone extra)
int					ft_parsing(char *str);

// UNSET
int					ft_unset(t_exec *exec);

t_node				*get_env_lst(char *to_find, t_node *lst);

//t_node node_bef);

// PWD
int					ft_pwd(t_exec *exec);

// EXIT
int					ft_exit(t_exec *exec);
long long int		ft_atoll(char *str, int i,
		long long int res, int sign);

// UITLS
char				**ft_free_willy(char **split);

#endif

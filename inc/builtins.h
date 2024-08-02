/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 16:59:25 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define F_NONE 0
# define F_ADD 1
# define F_CREATE 2

// CD
int					ft_cd(t_exec *exec);

// ENV
int					ft_env(t_exec *exec);
void				ft_print_env(t_node *env);

// EXPORT
int					ft_export(t_exec *exec);
//static int			ft_separate_export(t_env *env, t_exec *exec, char *str, int flag);
//static int			ft_create_env(t_env *env, char **cmd, char *str, int flag);
//static int			ft_add_replace_str_env(t_env *env, char **cmd, char *str, int flag);
//static int			ft_parsing(char *str);
int					ft_print_export(t_exec *exec);
int					ft_small_char(char **list, int i, int j, int k);
//static char			**ft_save_lst(t_node *env, char **list, int i);
//static int			ft_lstlen(t_node *env);
int					ft_count_list_elems(t_node *lst);
char				**ft_sort_lst_exp(char **lst, int i, int j, int pos);
//static int			ft_sorted(char **lst);
//static char			**ft_swap(char **lst, int pos, int i);
int					ft_find_char(char *str, char c);

// UNSET
int					ft_unset(t_exec *exec);
t_node 				*get_env_lst(char *to_find, t_node *lst);
char				**ft_free_willy(char **split);
//static t_node		*ft_get_env_before_lst(char *to_find, t_node *lst, t_exec *exec);
//static int			ft_extra_unset(t_exec *exec, t_node *node, t_node node_bef);

// PWD
int					ft_pwd(t_exec *exec);

// ECHO
int					ft_echo(t_exec *exec);

// EXIT
int					ft_exit(t_exec *exec);

#endif

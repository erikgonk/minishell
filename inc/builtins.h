/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/02 11:38:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define F_NONE 0
# define F_ADD 1
# define F_CREATE 2

// CD
int		ft_cd(t_exec *exec);

// ENV
int		ft_env(t_exec *exec);
void	ft_print_env(t_node *env);

// EXPORT
int					ft_export(t_exec *exec);
// static int		ft_separate_export(t_env *env, char **cmd, char *str, int flag);
// static void		ft_create_env(t_env *env, char **cmd, char *str, int flag);
// static void		ft_add_replace_str_env(t_env *env, char **cmd, char *str, int flag);
// static int		ft_parsing(char *str);
void				ft_print_export(t_exec *exec);
// static char		**ft_save_lst(t_node *env, char **list, int i);
// static int		ft_small_char(char **list, int i, int j, int k);
//static int		ft_lstlen(t_node *env);
int					ft_count_list_elems(t_node lst);
char				**ft_sort_lst_exp(char **list, int i, int j, int pos);
// static char		**ft_swap(char **list, int pos, int i);

// UNSET
int					ft_unset(t_exec *exec);
t_node 				*get_env_lst(char *to_find, t_node *lst);
char				**ft_free_willy(char **split);
// static t_node	*ft_get_env_before_lst(char *to_find, t_node *lst, t_node env);
// static int		ft_extra_unset(t_exec *exec, t_node *node, t_node node_bef);

// PWD
int					ft_pwd(t_exec *exec);

// ECHO
int					ft_echo(t_exec *exec);

// EXIT
int					ft_exit(t_exec *exec);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 13:29:27 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define F_NONE 0
# define F_ADD 1
# define F_CREATE 2

// CD
int					ft_cd(t_exec *exec);
static char			*ft_cd_normi(t_exec *exec, t_node *tmp, char *path);
static char			*ft_change_env_path(t_exec *exec,
		t_cmds *cmd, char *get);

// ECHO
int					ft_echo(t_exec *exec);
void				ft_n_checker(char **cmd, int i, int *flag);

// ENV
int					ft_env(t_exec *exec);
void				ft_print_env(t_node *env);

// EXPORT
int					ft_export(t_exec *exec);
static void			ft_export_normi(t_exec *exec, int i, int pos);
static int			ft_separate_export(t_env *env, t_exec *exec,
		char *str, int flag);
static int			ft_create_env(t_env *env, char **cmd, char *str,
		int flag);
static int			ft_add_replace_str_env(t_env *env, char **cmd,
		char *str, int flag);
// EXPORT_utils1 (for export alone)
int					ft_print_export(t_exec *exec);
static void			ft_printing(char **lst);
static char			**ft_save_lst(t_node *env, char **lst, int i);
int					ft_small_char(char **lst, int i, int j, int k);
static int			ft_lstlen(t_node *env);
// EXPORT_utils2 (general)
int					ft_find_char(char *str, char c);
int					ft_count_lst_elems(t_node *lst);
char				**ft_sort_lst_exp(char **lst, int i, int j, int pos);
static int			ft_sorted(char **lst);
static char			**ft_swap(char **lst, int pos, int i);
// EXPORT_utils3 (export alone extra)
int					ft_parsing(char *str);

// UNSET
int					ft_unset(t_exec *exec);
static int			ft_extra_unset(t_exec *exec, t_node *node, t_node *node_bef);
char				**ft_free_willy(char **split);

static t_node		*ft_get_env_before_lst(char *to_find, t_node *lst,
		t_node *env, t_exec *exec);
t_node				*get_env_lst(char *to_find, t_node *lst);

//t_node node_bef);

// PWD
int					ft_pwd(t_exec *exec);

// EXIT
int					ft_exit(t_exec *exec);
static void			ft_check_is_num(char *str);
long long int		ft_atoll(char *str, int i,
		long long int res, int sign);

#endif

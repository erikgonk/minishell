/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:44 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/14 12:17:14 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define TRUNC 0
# define ADD 1

// CD
int					ft_cd(t_exec *exec);

// ECHO
int					ft_echo(t_exec *exec);

// ENV
int					ft_env(t_exec *exec);
void				ft_print_env(t_node *env);

// EXPORT
int					ft_export(t_exec *exec);
// EXPORT_print (for export alone)
int					ft_print_export(t_node *node);
int					ft_small_char(char **lst, int i, int j, int k);
int					ft_find_char(char *str, char c);
int					ft_count_lst_elems(t_node *lst);
int					ft_parsing(char *str, int i);

// EXPORT_utils (normi)
int					ft_parsing_normi(char *str);
int					ft_export_flag(char *str);
char				*ft_export_get_var(char *str, int	flag);
char				*ft_export_get_str(t_exec *exec, char *cmd, int flag);
void				ft_just_a_printf();

// UNSET
int					ft_unset(t_exec *exec);

//t_node node_bef);

// PWD
int					ft_pwd(t_exec *exec);

// EXIT
int					ft_exit(t_exec *exec);
long long int		ft_atoll(char *str, int i,
		long long int res, int sign);

// UITLS
char				**ft_free_willy(char **cmd);
t_node				*ft_get_env_lst(char *to_find, t_node *lst);

#endif

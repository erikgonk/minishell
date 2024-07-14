/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:47 by erigonza          #+#    #+#             */
/*   Updated: 2024/07/12 11:22:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**ft_get_path(char **e)
{
	char		**res;
	int			i;

	i = -1;
	while (e[++i] && ft_strncmp("PATH", e[i], 4))
	{
		if (!e[i + 1])
			perror(e[i]);
	}
	res = ft_split(e[i], ':');
	*res += 5;
	return (res);
}

int	main(int argc, char **argv, char **env)
{
	t_exec		exec;

	if (argc != 5)
		perror("args");
	exec.paths = ft_get_path(env);
	exec.fd = open(argv[1], O_RDONLY);
	if (exec.fd < 0)
		perror("argv[1]");
	if (pipe(exec.tube) < 0)
		perror("Pipe Function");
	exec.pid1 = fork();
	if (exec.pid1 == 0)
		child(exec, argv, env);
	waitpid(pipex.pid1, NULL, -1);
	close(exec.fd);
	exit (0);
}

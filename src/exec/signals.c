/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:51:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/09 11:57:46 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include <signal.h>

void	ctrlc_hdoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	kill(0, SIGINT);
}

int	ft_get_stt(int flag, int val)
{
	static int	var;

	if (flag == 1)
		var = val;
	return (var);
}

// ----------------> add to main_loop
// signal(SIGINT, ft_sig_c);
// signal(SIGQUIT, SIG_IGN);
// data->g_exit = get_stt(0, 0);
// controls Control + C
void	ft_sig_c(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_get_stt(1, 130);
	g_signal = sig;
}
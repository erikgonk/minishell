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
	signal(SIGINT, SIG_DFL);
	kill(0, SIGINT);
}

void	ft_sig_c(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = sig;
}
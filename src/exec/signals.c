/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:51:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/06 15:34:49 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/redirs.h"
#include <signal.h>

/*
// avoid ^C ^D...
void	ft_sig_innit(void)
{
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
*/

int	get_stt(int flag, int val)
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
	if (sig == SIGINT)
	{
		ft_printf(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_stt(1, 130);
	}
}

// controls Control + C in here doc
void	ft_sig_c_hdoc(int sig, t_data *data)
{
	if (sig == SIGINT)
	{
		data->g_exit = 130;
		ft_printf(1, "\n");
		exit(1);
	}
}

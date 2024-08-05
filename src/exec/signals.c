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

// controls Control + C
void	ft_sig_c(int sig, t_data *data)
{
	if (sig == SIGINT)
	{
		data->g_exit = 130;
		ft_printf("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// controls Control + C in here doc
void	ft_sig_c_hdoc(int sig, t_data *data)
{
	if (sig == SIGINT)
	{
		data->g_exit = 130;
		ft_printf("\n", 2);
		exit(1);
	}
}

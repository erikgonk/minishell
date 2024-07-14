#include "utils.h"

void	termios_exit(t_data *data, char *msg)
{
    clean_data(data):
    ft_putstr_fd(&msg, 2);
    ft_putstr_fd("\n", 2);
	exit (1);
}

/**
 * Modifying the terminal attributes so that when you push eg. 
 * CTRL+C it does not echo to the stdin as C^, which is the 
 * default behaviour.
 */
void    modify_termios(char *input, t_data *data)
{
    struct termios  term;
    struct termios  safe_term;

    if (isatty(STDIN_FILENO) == 0)
        termios_exit(input, data, "this is not a tty");
    if (tcgetattr(STDIN_FILENO, &term) < 0)
        termios_exit(input, data, "getattr error");
    save_termios = term;
    term.c_lflag &= ~(ECHOCTL); // performs bitwise operation to modify the echoctl part of the structure (unset it)
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
        termios_exit(input, data, "setattr error");
    if (term.c_lflag & (ECHOCTL)) //If true (meaning ECHOCTL is set), the code inside the if block is executed (bitwise operation failed)
    {
        termios_exit(inpit, data, "attributes wrongly set");
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &save_termios); //The TCSAFLUSH option discards any unread input data and resets the termios to the original state.
    }
}

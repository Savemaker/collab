#include "minishell.h"

char *check_sig_code(int sig_code)
{
	if (sig_code == SIGINT)
		return (": Interrupt\n");
	return (NULL);
}

void print_signal(char *reason, int sig_code)
{
	ft_putstr_fd(reason, STDIN_FILENO);
	ft_putstr(check_sig_code(sig_code));
}



void handler_interrupt(int signal)
{
  if (signal == SIGINT)
    siglongjmp(g_sig, 1);
}

void signals()
{
	signal(SIGINT, handler_interrupt);
}

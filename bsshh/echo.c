#include "minishell.h"

int echo_cmnd(char **args)
{
	int i;
	int argc;

	i = 1;
	argc  = 0;
	while(args[argc])
		argc++;
	while (args[i])
	{

		if (!ft_strcmp(" ", args[i]))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if ((argc - 1) != i)
			ft_putchar_fd(' ', STDOUT_FILENO);

		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (1); //continue to execute
}
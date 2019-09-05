#include "minishell.h"

int launch(char *file, char **args)
{
	pid_t pid;
	int status;

	pid = fork(); // make copy of process (child)
	if (pid == 0) // child process
	{
		if (execve(file, args, g_env) == -1) //replace current running process with new one
			perror_cmnd("minishell", NULL, EXECVEERR);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) // fork error
		perror_cmnd("minishell", NULL, FORKERR);
	else // parent process
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		//		if (WIFSIGNALED(status))
		//print_signal("\nChild term due to", status);
	}
	free(file);
	return (1); //continue to execute
}

int		absolute_path_launch(char **cmnd)
{
	if (access(cmnd[0], X_OK))
	{
		if (access(cmnd[0], F_OK) == -1)
			perror_cmnd("minishell", cmnd[0], CMNDNTFND);
		else
			perror_cmnd("minishell", cmnd[0], PMDND);
		return(1);
	}
	return (launch(cmnd[0], cmnd));
}

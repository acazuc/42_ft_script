#include "ft_script.h"

int	do_the_fork(t_env *env)
{
	char	*args[2];
	pid_t	pid;

	if ((pid = fork()) == -1)
		return (0);
	if (pid == 0)
	{
		if (dup2(env->pty_sfd, 0) == -1 || dup2(env->pty_sfd, 1) == -1 || dup2(env->pty_sfd, 2) == -1)
			_exit(EXIT_FAILURE);
		//setsid();
		args[0] = env->shell;
		args[1] = NULL;
		execve(env->shell, args, env->ev);
		_exit(EXIT_FAILURE);
	}
	return (1);
}

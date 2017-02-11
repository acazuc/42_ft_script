#include "ft_script.h"

static void	init_sets(t_env *env, fd_set *sets)
{
	FD_ZERO(&sets[0]);
	FD_ZERO(&sets[1]);
	FD_SET(0, &sets[0]);
	FD_SET(env->pty_mfd, &sets[0]);
	FD_SET(0, &sets[1]);
	FD_SET(env->pty_mfd, &sets[1]);
}

static void	do_transfer(int dst, int src)
{
	char	buf[4096];
	ssize_t	readed;

	if ((readed = read(src, buf, 4096)) <= 0)
	{
		ft_putstr_fd("read() failed", 2);
		_exit(EXIT_FAILURE);
	}
	readed = write(dst, buf, readed);
}

static void	do_transfer_2(int dst, int dst2, int src)
{
	char	buf[4096];
	ssize_t	readed;

	if ((readed = read(src, buf, 4096)) <= 0)
	{
		ft_putstr_fd("read() failed", 2);
		_exit(EXIT_FAILURE);
	}
	readed = write(dst, buf, readed);
	readed = write(dst2, buf, readed);
}

void	loop(t_env *env)
{
	fd_set	sets[2];

	while (1)
	{
		init_sets(env, sets);
		if (select(env->pty_mfd + 1, &sets[0], NULL, &sets[1], NULL) == -1)
		{
			ft_putstr_fd("select() failed\n", 2);
			_exit(EXIT_FAILURE);
		}
		if (FD_ISSET(0, &sets[1]))
		{
			ft_putstr_fd("exception on stdin fd\n", 2);
			_exit(EXIT_FAILURE);
		}
		if (FD_ISSET(env->pty_mfd, &sets[1]))
		{
			ft_putstr_fd("exception on pty fd\n", 2);
			_exit(EXIT_FAILURE);
		}
		if (FD_ISSET(0, &sets[0]))
			do_transfer(env->pty_mfd, 0);
		if (FD_ISSET(env->pty_mfd, &sets[0]))
			do_transfer_2(env->file_fd, 1, env->pty_mfd);
	}
}

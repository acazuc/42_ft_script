#include "ft_script.h"

static void	set_ioctl(t_env *env)
{
	struct termios	caps;
	struct winsize	wins;

	if (ioctl(env->pty_mfd, TCGETS, &caps) == -1)
		_exit(EXIT_FAILURE);
	if (ioctl(env->pty_sfd, TCSETSF, &caps) == -1)
		_exit(EXIT_FAILURE);
	if (ioctl(env->pty_mfd, TIOCGWINSZ, &wins) == -1)
		_exit(EXIT_FAILURE);
	if (ioctl(env->pty_sfd, TIOCSWINSZ, &wins) == -1)
		_exit(EXIT_FAILURE);
}

int	open_pty(t_env *env)
{
	char	pty_sname[128];
	int	i;
	int	sid;

	if ((env->pty_mfd = open("/dev/ptmx", O_RDWR)) == -1)
		return (0);
	ft_memcpy(pty_sname, "/dev/pts/", 10);
	sid = 0;
	if (ioctl(env->pty_mfd, TIOCSPTLCK, &sid) == -1)
		_exit(EXIT_FAILURE);
	if (ioctl(env->pty_mfd, TIOCGPTN, &sid) == -1)
		_exit(EXIT_FAILURE);
	i = 9;
	if (sid >= 100)
		pty_sname[i++] = '0' + (sid / 100) % 10;
	if (sid >= 10)
		pty_sname[i++] = '0' + (sid / 10) % 10;
	pty_sname[i++] = '0' + sid % 10;
	pty_sname[i] = '\0';
	if ((env->pty_sfd = open(pty_sname, O_RDWR)) == -1)
		return (0);
	set_ioctl(env);
	return (1);
}

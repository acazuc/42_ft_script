#include "ft_script.h"

int	open_pty(t_env *env)
{
	char	pty_sname[15];
	int	i;

	if ((env->pty_mfd = open("/dev/ptmx", O_RDWR)) == -1)
		return (0);
	ft_memcpy(pty_sname, "/dev/pts/", 10);
	i = 9;
	if (env->pty_mfd >= 100)
		pty_sname[i++] = '0' + (env->pty_mfd / 100) % 10;
	if (env->pty_mfd >= 10)
		pty_sname[i++] = '0' + (env->pty_mfd / 10) % 10;
	pty_sname[i++] = '0' + env->pty_mfd % 10;
	pty_sname[i] = '\0';
	if ((env->pty_sfd = open(pty_sname, O_RDWR)) == -1)
		return (0);
	return (1);
}

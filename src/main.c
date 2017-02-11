#include "ft_script.h"

static char	*get_shell(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp("SHELL=", ev[i], 6))
			return (ev[i] + 6);
		++i;
	}
	return ("/bin/sh");
}

static void	open_file(t_env *env)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!env->arg_a)
		flags |= O_TRUNC;
	if ((env->file_fd = open(env->filename, flags, 0644)) == -1)
	{
		ft_putstr_fd("Failed to open output file\n", 2);
		_exit(EXIT_FAILURE);
	}
}

int		main(int ac, char **av, char **ev)
{
	t_env	env;
	int	fpos;

	ft_memset(&env, 0, sizeof(env));
	env.ev = ev;
	fpos = parse_args(&env, ac, av);
	if (fpos >= ac)
		env.filename = "typescript";
	else
		env.filename = av[fpos];
	env.shell = get_shell(ev);
	open_file(&env);
	if (!open_pty(&env))
	{
		ft_putstr_fd("Failed to open pty\n", 2);
		return (EXIT_FAILURE);
	}
	if (!(env.pid = do_the_fork(&env)))
	{
		ft_putstr_fd("Failed to fork\n", 2);
		return (EXIT_FAILURE);
	}
	loop(&env);
	return (EXIT_SUCCESS);
}

#include "ft_script.h"

static int	parse_arg(t_env *env, char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'a')
			env->arg_a = 1;
		else if (str[i] == 'q')
			env->arg_q = 1;
		else if (str[i] == '-')
			return (1);
		else

		++i;
	}
	return (0);
}

int	parse_args(t_env *env, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-')
			break;
		if (parse_arg(env, av[i]))
			return (i + 1);
		++i;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 01:19:23 by acazuc            #+#    #+#             */
/*   Updated: 2017/02/11 01:19:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "../libft/include/libft.h"
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <fcntl.h>
# include <term.h>

typedef struct s_env	t_env;

int	parse_args(t_env *env, int ac, char **av);
int	open_pty(t_env *env);
int	do_the_fork(t_env *env);
void	loop(t_env *env);

struct			s_env
{
	char		**ev;
	char		*filename;
	char		*shell;
	int		arg_a;
	int		arg_q;
	int		file_fd;
	int		pty_mfd;
	int		pty_sfd;
	pid_t		pid;
};

#endif

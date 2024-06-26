/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:05:00 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 20:54:44 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_exit_status(char *str)
{
	int	exit_status;

	exit_status = ft_atoi(str);
	if (exit_status < 0)
		exit_status = 256 + (exit_status % 256);
	return (exit_status % 256);
}

void	bjsh_exit(t_bjsh *bjsh, char **args)
{
	if (args[1])
	{
		if (ft_isnumeric(args[1]))
		{
			if (args[2])
			{
				ft_dprintf(STDERR_FILENO, "🤌 ❯ exit: too many arguments\n");
				bjsh->last_exit_status = 1;
				return ;
			}
			bjsh->last_exit_status = get_exit_status(args[1]);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "🤌 ❯ exit: %s: numeric argument required\n",
				args[1]);
			bjsh->last_exit_status = 2;
		}
	}
	bjsh->state = NOT_CHILLING;
	blyat_(bjsh);
}

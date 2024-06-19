/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:44:15 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/18 19:16:06 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (isatty(STDIN_FILENO)) // Check if in interactive mode
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
//	else if (sig == SIGTSTP) // ctrl+z
//	{
//		ft_putstr_fd("\n", 1);
//		ft_putstr_fd("SIGTSTP received. Suspending process.\n", 1);
//	}
}

void	handle_eof(void)
{
	if (isatty(STDIN_FILENO)) // Check if in interactive mode
	{
		exit(0); // ctrl+D, exit the shell
	}
}

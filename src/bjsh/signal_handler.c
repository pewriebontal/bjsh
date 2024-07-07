/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:44:15 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/08 03:31:07 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
		{
			ft_putstr_fd("Quit: 3\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (sig == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
	}
}

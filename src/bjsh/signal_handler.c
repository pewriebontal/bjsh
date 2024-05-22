/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:44:15 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/22 20:52:55 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt_msg();
	}
	if (sig == SIGTSTP)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("SIGTSTP received. Suspending process.\n", 1);
	}
}

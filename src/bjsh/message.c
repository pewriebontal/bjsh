/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:43:56 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 03:00:02 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char *get_shell_prompt(t_bjsh *bjsh)
{
	if(bjsh->last_exit_status == 0)
		return ("👌 ❯ ");
	else if(bjsh->last_exit_status == 1)
		return ("👎 ❯ ");
	else 
		return ("👍 ❯ ");
}


void	display_prompt_msg(void)
{
	ft_putstr_fd("👍 ❯ ", 1);
}

void	display_error_msg(char *msg)
{
	ft_putstr_fd("👎 ❯ ", 1);
	ft_putstr_fd(msg, 1);
}

void	display_info_msg(char *msg)
{
	ft_putstr_fd("👌 ❯ ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}

void	display_warning_msg(char *msg)
{
	ft_putstr_fd("👀 ❯ ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}

void	display_success_msg(char *msg)
{
	ft_putstr_fd("👏 ❯ ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:43:56 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 01:02:28 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char	*get_shell_prompt(t_bjsh *bjsh)
{
	if (bjsh->last_exit_status == 0)
		return ("👌 ❯ ");
	else if (bjsh->last_exit_status != 0)
		return ("🤌 ❯ ");
	else
		return ("🍒 ❯ ");
}

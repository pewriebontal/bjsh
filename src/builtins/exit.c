/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:05:00 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/25 01:45:54 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_exit(t_bjsh *bjsh, char *args)
{
	int	custom_exit_status;

	if (args)
	{
		custom_exit_status = ft_atoi(args);
		bjsh->state = NOT_CHILLING;
		exit(custom_exit_status);
	}
	bjsh->state = NOT_CHILLING;
	atexit(handle_eof);
	exit(bjsh->last_exit_status);
}

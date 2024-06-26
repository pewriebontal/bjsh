/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:05:00 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 16:53:59 by mkhaing          ###   ########.fr       */
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
		bjsh->last_exit_status = custom_exit_status;
		blyat_(bjsh);
	}
	bjsh->state = NOT_CHILLING;
	blyat_(bjsh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:57:36 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/25 02:02:53 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_debug_msg(char *msg)
{
	if (DEBUG_MODE == 1)
	{
		ft_printf("DEBUG: %s\n", msg);
	}
}

int	bjsh_show_error(char *msg)
{
	ft_printf("🍦bjsh👎: %s\n", msg);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}
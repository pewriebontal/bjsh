/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:49:32 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/06 21:26:52 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_help(void)
{
	ft_printf("%s (%s) [%s \"%s\" %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
		SHELL_VERSION, GIT_COMMIT, SHELL_BUILD_DATE);
	ft_printf("Usage: %s [OPTION]...\n", SHELL_SHORT_NAME);
	ft_printf("  --version\t\tprint version and exit\n");
	ft_printf("  --help\t\tprint this help and exit\n");
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	print_version(void)
{
	ft_printf("%s (%s) [%s \"%s\" %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
		SHELL_VERSION, GIT_COMMIT, SHELL_BUILD_DATE);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

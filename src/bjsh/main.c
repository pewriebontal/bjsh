/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 22:20:26 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_bjsh(t_bjsh *bjsh, char *env[])
{
	bjsh->status = CHILLING;
	bjsh->envp = env;
	bjsh_hist_file_create();
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	main(int argc, char *argv[], char *env[])
{
	t_bjsh	bjsh;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "--version", 10) == 0)
		{
			ft_printf("%s (%s) [%s %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
				SHELL_VERSION, SHELL_BUILD_DATE);
			return (UNDERSTOOD_THE_ASSIGNMENT);
		}
		if (ft_strncmp(argv[1], "--help", 7) == 0)
		{
			ft_printf("%s (%s) [%s %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
				SHELL_VERSION, SHELL_BUILD_DATE);
			ft_printf("Usage: %s [OPTION]...\n", SHELL_SHORT_NAME);
			ft_printf("  --version\t\tprint version and exit\n");
			ft_printf("  --help\t\tprint this help and exit\n");
			return (UNDERSTOOD_THE_ASSIGNMENT);
		}
	}
	init_bjsh(&bjsh, env);
	bjsh_loop(&bjsh);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

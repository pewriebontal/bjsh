/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 05:09:27 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_bjsh(t_bjsh *bjsh, char *env[])
{
	char	*history_file_path;

	history_file_path = bjsh_get_history_path();
	bjsh_hist_file_create();
	bjsh_read_history(history_file_path);
	bjsh->state = CHILLING;
	bjsh->last_exit_status = 0;
	bjsh->envp = env;
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	main(int argc, char *argv[], char *env[])
{
	t_bjsh	bjsh;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "--version", 10) == 0)
		{
			ft_printf("%s (%s) [%s \"%s\" %s]\n", SHELL_SHORT_NAME,
				SHELL_LONG_NAME, SHELL_VERSION, GIT_COMMIT, SHELL_BUILD_DATE);
			return (UNDERSTOOD_THE_ASSIGNMENT);
		}
		if (ft_strncmp(argv[1], "--help", 7) == 0)
		{
			ft_printf("%s (%s) [%s \"%s\" %s]\n", SHELL_SHORT_NAME,
				SHELL_LONG_NAME, SHELL_VERSION, GIT_COMMIT, SHELL_BUILD_DATE);
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

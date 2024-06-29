/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 16:44:14 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	blyat_(t_bjsh *bjsh)
{
	if (isatty(STDIN_FILENO))
	{
		yeet_history_path(bjsh);
		rl_clear_history();
		ft_dprintf(STDOUT_FILENO, "blyat\n");
		if (bjsh->token)
			yeet_token(bjsh->token);
		if (bjsh->history_path)
			yeet(bjsh->history_path);
		if (!bjsh->first_run)
		{
			if (bjsh->envp)
				ft_free_multidi((void **)bjsh->envp, 2);
		}
		if (bjsh->env)
			yeet_env(bjsh->env);
		exit(bjsh->last_exit_status);
	}
}

int	init_bjsh(t_bjsh *bjsh, char *env[])
{
	bjsh->history_path = bjsh_get_history_path();
	bjsh_hist_file_create();
	bjsh_read_history(bjsh->history_path);
	bjsh->state = CHILLING;
	bjsh->last_exit_status = 0;
	bjsh->first_run = 1;
	bjsh->envp = env;
	bjsh_env_init(bjsh);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	main(int argc, char *argv[], char *env[])
{
	t_bjsh	bjsh;

	bjsh = (t_bjsh){0};
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
	return (bjsh.last_exit_status);
}

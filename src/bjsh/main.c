/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/06 23:50:53 by mkhaing          ###   ########.fr       */
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
		if (bjsh->token != NULL)
		{
			yeet_token(bjsh->token);
			bjsh->token = NULL;
		}
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

void	increase_shlvl(t_bjsh *bjsh)
{
	t_env	*shlvl_node;
	int		shlvl;

	shlvl_node = find_env_node(bjsh->env, "SHLVL");
	if (shlvl_node)
	{
		shlvl = ft_atoi(shlvl_node->value);
		free(shlvl_node->value);
		shlvl_node->value = ft_itoa(shlvl + 1);
	}
	else
	{
		bjsh_export(bjsh, "SHLVL", "1");
	}
}

int	init_bjsh(t_bjsh *bjsh, char *env[])
{
	bjsh->history_path = bjsh_get_history_path();
	bjsh_hist_file_create();
	bjsh_read_history(bjsh->history_path);
	bjsh->state = CHILLING;
	bjsh->last_exit_status = 0;
	bjsh->token = NULL;
	bjsh->first_run = 1;
	bjsh->envp = env;
	bjsh_env_init(bjsh);
	increase_shlvl(bjsh);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	param_c(char *command, t_bjsh *bjsh)
{
	t_token	*token;

	token = bon_and_jason_tokenizer(command, bjsh);
	execute_tokens(token, bjsh);
	return (bjsh->last_exit_status);
}

int	main(int argc, char *argv[], char *env[])
{
	t_bjsh	bjsh;
	char	*argum;
	int		exit_status;

	bjsh = (t_bjsh){0};
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "--version", 10) == 0)
			print_version();
		if (ft_strncmp(argv[1], "--help", 7) == 0)
			print_help();
	}
	init_bjsh(&bjsh, env);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		argum = ft_strdup(argv[2]);
		exit_status = param_c(argum, &bjsh);
		exit(exit_status);
	}
	bjsh_loop(&bjsh);
	return (bjsh.last_exit_status);
}

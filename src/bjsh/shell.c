/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/20 22:40:10 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	char *line;
	char **args;

	while (bjsh->status == CHILLING)
	{
		spill_the_tea("🍦bjsh👍 ");
		line = get_next_line(1);

		// ft_printf("You said: %s\n", line);

		args = ft_split(line, ' ');

		if (args[0] == NULL)
		{
			free(line);
			continue ;
		}
		if (ft_strncmp(args[0], "exit", 4) == 0)
		{
			bjsh->status = NOT_CHILLING;
		}
		else if (ft_strncmp(args[0], "cd", 2) == 0)
		{
			char *path = args[1];
			path = ft_strjoin(path, "/");
			bjsh_cd(path);
		}
		else if (ft_strncmp(args[0], "pwd", 3) == 0)
		{
			bjsh_pwd();
		}
		else if (ft_strncmp(args[0], "help", 4) == 0)
		{
			bjsh_help(args);
		}
		else
		{
			bjsh_exec(args);
		}

		free(line);
	}
}
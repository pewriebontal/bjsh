/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 14:21:44 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (bjsh->state == CHILLING)
	{
		line = readline(SHELL_PROMPT);
		if (!line)
			break ;
		line[strcspn(line, "\n")] = 0;
		if (*line)
			add_history(line);
		token = bon_and_jason_tokenizer(line, bjsh);
		execute_tokens(token, bjsh);
		if (token)
			clear_list(token);
	}
}

int	check_builtin(char *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUGGI_BAKA);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (BUGGI_BAKA);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (SUSSY_BAKA);
	else if (ft_strcmp(cmd, "help") == 0)
		return (SUSSY_BAKA);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (SUSSY_BAKA);
	else if (ft_strcmp(cmd, "export") == 0)
		return (BUGGI_BAKA);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (BUGGI_BAKA);
	else if (ft_strcmp(cmd, "env") == 0)
		return (SUSSY_BAKA);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_exec_builtin(char **args, t_bjsh *bjsh)
{
	char	*path;

	if (ft_strcmp(args[0], "exit") == 0)
		return (bjsh_exit(bjsh, args[1]));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (bjsh_cd(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (bjsh_pwd());
	else if (ft_strcmp(args[0], "help") == 0)
		return (bjsh_help(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (bjsh_echo(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (bjsh_export(bjsh, args[1], args[2]));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (bjsh_unset(bjsh, args[1]));
	else if (ft_strcmp(args[0], "env") == 0)
		return (bjsh_env(bjsh));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/18 15:01:25 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	char	*line;
	char	**args;
	char	*history_file_path;
	t_token	*token;

	history_file_path = bjsh_get_history_path();
	bjsh_read_history(history_file_path);
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ is ignored
	while (bjsh->state == CHILLING)
	{
		line = readline(SHELL_PROMPT);
		if (!line) // if ctrl-D is pressed
			break ;
		line[strcspn(line, "\n")] = 0;
		if (*line)
			add_history(line);
		write_history(history_file_path);
		token = bon_and_jason_tokenizer(line);
		//debug_print_list(token);
		execute_tokens(token, bjsh);
		clear_list(token);
	}
	write_history(history_file_path);
}

int	check_builtin(char *cmd)
{
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
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_exec_builtin(char **args, t_bjsh *bjsh)
{
	char *path;

	if (ft_strcmp(args[0], "exit") == 0)
	{
		bjsh_exit(bjsh);
		return (1);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		path = chope(1024);
		ft_memset(path, 0, 1024);
		ft_strlcpy(path, args[1], ft_strlen(args[1]) + 1);
		path[ft_strlen(path) + 1] = '\0';
		bjsh_cd(path);
		free(path);
		return (1);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		bjsh_pwd();
		return (1);
	}
	else if (ft_strcmp(args[0], "help") == 0)
	{
		bjsh_help(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		bjsh_echo(args);
		return (1);
	}
	return (0);
}
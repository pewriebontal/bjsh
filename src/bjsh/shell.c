/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 17:06:41 by mkhaing          ###   ########.fr       */
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
	read_history(history_file_path);
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ is ignored
	while (bjsh->status == CHILLING)
	{
		line = readline(SHELL_PROMPT);
		if (!line) // if ctrl-D is pressed
			break ;
		line[strcspn(line, "\n")] = 0;
		if (*line)
			add_history(line);
		write_history(history_file_path);
		token = bon_and_jason_tokenizer(line);
		execute_tokens(token, bjsh->envp);
		clear_list(token);
	}
	write_history(history_file_path);
}

int	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "help", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	return (0);
}

int	bjsh_exec_builtin(char **args)
{
	char *path;

	if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		bjsh_exit();
		return (1);
	}
	else if (ft_strncmp(args[0], "cd", 3) == 0)
	{
		path = chope(1024);
		ft_memset(path, 0, 1024);
		ft_strlcpy(path, args[1], ft_strlen(args[1]) + 1);
		// null terminate the path
		path[ft_strlen(path) + 1] = '\0';
		bjsh_cd(path);
		free(path);
		return (1);
	}
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
	{
		bjsh_pwd();
		return (1);
	}
	else if (ft_strncmp(args[0], "help", 5) == 0)
	{
		bjsh_help(args);
		return (1);
	}
	else if (ft_strncmp(args[0], "echo", 5) == 0)
	{
		bjsh_echo(args);
		return (1);
	}
	return (0);
}
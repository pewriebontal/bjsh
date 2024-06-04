/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/04 23:36:01 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	char	*line;
	char	**args;
	char	*history_file_path;

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
		args = ft_split(line, ' ');
		// args = parse_command(line);
		if (args && *args)
			pre_execute(args, bjsh);
		free(line);
		ft_free_multi_dimensional_array((void **)args, 2);
	}
}

int	pre_execute(char **args, t_bjsh *bjsh)
{
	if (args[0] == NULL)
		return (1);
	if (check_builtin(args[0]))
	{
		if (bjsh_exec_builtin(args))
			return (1);
	}
	else
	{
		bjsh_exec(args, bjsh);
	}
	return (1);
}

int	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "help", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
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
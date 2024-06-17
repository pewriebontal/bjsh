/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 16:20:20 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	char	*line;
	char	**args;
	char	*history_file_path;
	t_token	*token;
	char	**test;
	int		a;

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
		replace_spaces_in_quotes(line);
		//	ft_printf("line: %s\n", line);
		// args = ft_split(line, '"');
		// line = NULL;
		// line = ft_rejoin_arr(args);
		//	ft_printf("line: %s\n", line);
		// args = ft_split(line, '\'');
		// line = ft_rejoin_arr(args);
		args = ft_split(line, ' ');
		///
		token = array_to_list(args);
		//	debug_print_list(token);                   //remove cmt.
		///
		//	ft_printf("================\n");			// remove cmt.
		///
		token = token_split_redirect(token);
		//		token = token_split_redirect(token);
		evaluate_token_chain(token);
		replace_special_characters_in_node(token);
		token = remove_quotes_from_token(token);
		execute_tokens(token, bjsh->envp);
		//		execute_command(token);
		//	debug_print_list(token);                      // remove cmt.
		///
		//	ft_printf("================\n");              // remove cmt.
		///
		//	test = lst_to_arr(token);
		// debug_print_arr(test);
		// set_token_list(bjsh, line);
		// args = parse_command(line);
		// execute_pipe(bjsh, args[0], args[1]);
		// execute_pipe(bjsh, args[0], args[1]);
		// if (args && *args)
		// 	pre_execute(args, bjsh);
		clear_list(token);
		free(line);
		//		ft_free_multidi((void **)args, 2);
		// ft_free_multidi((void **)test, 2);
		write_history(history_file_path);
	}
	//	free(history_file_path);
	//	ft_free_multidi((void **)args, 2);
	//	ft_free_multidi((void **)test, 2);
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
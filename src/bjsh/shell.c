/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klinn <klinn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/25 16:25:52 by klinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bjsh_loop(t_bjsh *bjsh)
{
	t_bjsh bjsh;
	char	*line;
	char	**args;
	char	*path;
	char	*history_file_path;
	char	*prompt;

	prompt = "🍦bjsh👍 ";
	history_file_path = bjsh_get_history_path();
	read_history(history_file_path);
	while (bjsh->status == CHILLING)
	{
		// display_prompt_msg();
		signal(SIGINT, handle_signal);
		signal(SIGTSTP, handle_signal);
		// line = get_next_line(1);
		// line = readline(prompt);
		// line[strcspn(line, "\n")] = 0;
		bjsh->argv = readline(prompt);
		bjsh->argv[strcspn(bjsh->argv, "\n")] = 0;

		save_token(bjsh);
		bjsh_hist_file_append(bjsh->argv);
		add_history(bjsh->argv);
		//  TODO: replace with own implementation// ft_strtrim
		args = ft_split(line, ' ');
		if (args[0] == NULL)
		{
			free(bjsh->argv);
			continue ;
		}
		if (ft_strncmp(args[0], "exit", 5) == 0)
		{
			write_history(history_file_path);
			bjsh->status = NOT_CHILLING;
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
		}
		else if (ft_strncmp(args[0], "pwd", 4) == 0)
		{
			bjsh_pwd();
		}
		else if (ft_strncmp(args[0], "help", 5) == 0)
		{
			bjsh_help(args);
		}
		else
		{
			bjsh_exec(args);
		}
		free(line);
		ft_free_multi_dimensional_array((void **)args, 2);
	}
}

// combine all the builtin commands into one function
//  ??????????????????????
void	run_cmd(t_bjsh *bjsh, char **args)
{
	char	*path;

	if (args[0] == NULL)
	{
		// free(line);
		// continue ;
	}
	if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		bjsh->status = NOT_CHILLING;
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
	}
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
	{
		bjsh_pwd();
	}
	else if (ft_strncmp(args[0], "help", 5) == 0)
	{
		bjsh_help(args);
	}
	else
	{
		bjsh_exec(args);
	}
}

// if detected pipe, do run the next command
//* need to change ptr before pasing to run_cmd
// void pipe(t_bjsh *bjsh, char **args)
//{
//	int i;
//
//	i = 0;
//	while (args[i])
//	{
//		if (ft_strncmp(args[i], "|", 2) == 0)
//		{
//			run_cmd(bjsh, args);
//		}
//		i++;
//	}
//}
//
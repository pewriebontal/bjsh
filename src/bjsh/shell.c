/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:07:03 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 17:38:23 by mkhaing          ###   ########.fr       */
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
			blyat_(bjsh);
		if (*line)
		{
			add_history(line);
			bjsh_hist_add_entry(line);
		}
		token = bon_and_jason_tokenizer(line, bjsh);
		execute_tokens(token, bjsh);
		if (!bjsh->first_run)
			ft_free_multidi((void **)bjsh->envp, 2);
		bjsh->envp = convert_env_to_envp(bjsh->env);
		if (token)
			clear_list(token);
		bjsh->first_run = 0;
	}
	blyat_(bjsh);
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
	if (ft_strcmp(args[0], "exit") == 0)
		bjsh_exit(bjsh, args[1]);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (bjsh_cd(args, bjsh));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (bjsh_pwd());
	else if (ft_strcmp(args[0], "help") == 0)
		return (bjsh_help());
	else if (ft_strcmp(args[0], "echo") == 0)
		return (bjsh_echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (bjsh_env(bjsh));
	else if (ft_strcmp(args[0], "export") == 0)
		return (handle_export_command(bjsh, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (handle_unset_command(bjsh, args));
	return (0);
}

int	handle_export_command(t_bjsh *bjsh, char **args)
{
	char	*equal_sign;
	int		result;

	if (args[1])
	{
		equal_sign = ft_strchr(args[1], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			result = bjsh_export(bjsh, args[1], equal_sign + 1);
			*equal_sign = '=';
			return (result);
		}
		else
			return (bjsh_export(bjsh, args[1], ""));
	}
	else
		return (bjsh_env(bjsh));
}

int	handle_unset_command(t_bjsh *bjsh, char **args)
{
	if (args[1])
		return (bjsh_unset(bjsh, args[1]));
	else
		return (0);
}

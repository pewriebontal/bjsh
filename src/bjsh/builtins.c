/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/18 19:03:25 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_help(char **args)
{
	ft_printf("%s (%s) [%s %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
		SHELL_VERSION, SHELL_BUILD_DATE);
	ft_printf("💀 No help available!🫣🤭\n");
	ft_printf("😗 Go cry about it! 🤓🙊\n");
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_echo(char **args)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_cd(char *path)
{
	if (path == NULL || *path == '\0')
	{
		path = getenv("HOME");
	}
	if (chdir(path) == -1)
	{
		display_error_msg("cd: no such file or directory: ");
		ft_printf("%s\n", path);
		return (BUSTED);
	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		yeet(buf);
	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_export(void)
{
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_unset(void)
{
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_env(t_bjsh *bjsh)
{
	//	t_env	*env;
	//
	//	env = bjsh->env;
	//	while (env)
	//	{
	//		ft_printf("%s=%s\n", env->key, env->value);
	//		env = env->next;
	//	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_exit(t_bjsh *bjsh)
{
	bjsh->state = NOT_CHILLING;
	atexit(handle_eof); // handle EOF when the program exits
	exit(UNDERSTOOD_THE_ASSIGNMENT);
}
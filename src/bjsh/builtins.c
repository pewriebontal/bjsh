/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/24 17:58:10 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_cd(char *path)
{
	// if no path is given, go to the home directory
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
		ft_printf("%s\n", buf);
		yeet(buf);
	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_exit(void)
{
	exit(UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_echo(char **args)
{
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_help(char **args)
{
	ft_printf("%s (%s) [%s %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
		SHELL_VERSION, SHELL_BUILD_DATE);
	ft_printf("No help available!🫣😗🤭\n");
	ft_printf("Go cry about it!🤓🙊");
	ft_printf("\n");
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

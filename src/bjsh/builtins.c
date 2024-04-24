/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/25 02:23:54 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_cd(char *path)
{
	if (chdir(path) != 0)
	{
		ft_printf("🍦bjsh👎: %s : No such file or directory\n", path);
	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	bjsh_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_printf("%s\n", buf);
	yeet(buf);
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
	spill_the_tea("No Help!\n");
	spill_the_tea("go cry about it!\n");
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

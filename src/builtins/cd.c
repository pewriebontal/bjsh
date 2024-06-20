/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/21 00:33:11 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path(char **args)
{
	char	*path;

	path = chope(1024);
	ft_memset(path, 0, 1024);
	ft_strlcpy(path, args[1], ft_strlen(args[1]) + 1);
	path[ft_strlen(path) + 1] = '\0';
	return (path);
}

int	bjsh_cd(char **args)
{
	char	*path;

	path = get_path(args);
	if (path == NULL || *path == '\0')
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		display_error_msg("cd: no such file or directory: ");
		ft_printf("%s\n", path);
		return (1);
	}
	return (0);
}

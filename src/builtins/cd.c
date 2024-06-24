/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/25 02:28:05 by mkhaing          ###   ########.fr       */
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

int	bjsh_cd(char **args, t_bjsh *bjsh)
{
	char	*path;

	if (args[1] && args[2])
	{
		ft_dprintf(STDERR_FILENO, "🤌 ❯ cd: too many arguments\n");
		return (1);
	}
	path = get_path(args);
	if (path == NULL || *path == '\0')
		path = get_env_local(bjsh->envp, "HOME");
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "🤌 ❯ cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

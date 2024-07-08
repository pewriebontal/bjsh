/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/08 20:16:19 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path(char **args)
{
	char	*path;

	path = chope(1024);
	ft_memset(path, 0, 1024);
	if (args[1])
		ft_strlcpy(path, args[1], ft_strlen(args[1]) + 1);
	path[ft_strlen(path) + 1] = '\0';
	return (path);
}

char	*handle_no_path_set(t_bjsh *bjsh)
{
	char	*env_path;
	char	*path;

	env_path = get_env_local2(bjsh->env, "HOME");
	if (env_path == NULL || *env_path == '\0')
	{
		ft_dprintf(STDERR_FILENO, "🤌 ❯ cd: HOME not set\n");
		yeet(env_path);
		return (NULL);
	}
	path = ft_strdup(env_path);
	yeet(env_path);
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
	{
		yeet(path);
		path = handle_no_path_set(bjsh);
		if (path == NULL)
			return (1);
	}
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "🤌 ❯ cd: %s: %s\n", path, strerror(errno));
		yeet(path);
		return (1);
	}
	yeet(path);
	return (0);
}

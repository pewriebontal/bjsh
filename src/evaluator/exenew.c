/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exenew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:06:21 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 03:37:47 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_absolute_or_relative_path(const char *command)
{
	if (command[0] == '/' || (command[0] == '.' && (command[1] == '/'
				|| command[1] == '.')))
	{
		if (access(command, X_OK) == 0)
		{
			return (ft_strdup(command));
		}
		return (NULL);
	}
	return (NULL);
}

char	*get_path_env(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_strdup(path_env));
}

char	*construct_executable_path(const char *path, const char *command)
{
	char	*executable_path;

	executable_path = malloc(256);
	snprintf(executable_path, 256, "%s/%s", path, command);
	return (executable_path);
}

char	*search_in_paths(const char *command, char *path_env)
{
	char	*path;
	char	*executable_path;
	char	*constructed_path;

	path = ft_strtok(path_env, ":");
	executable_path = malloc(256);
	while (path)
	{
		constructed_path = construct_executable_path(path, command);
		if (access(constructed_path, X_OK) == 0)
		{
			free(executable_path);
			return (constructed_path);
		}
		free(constructed_path);
		path = ft_strtok(NULL, ":");
	}
	free(executable_path);
	return (NULL);
}

char	*find_executable(const char *command, char **envp)
{
	char	*executable_path;
	char	*path_env;

	executable_path = check_absolute_or_relative_path(command);
	if (executable_path)
		return (executable_path);
	path_env = get_path_env();
	if (!path_env)
		return (NULL);
	executable_path = search_in_paths(command, path_env);
	free(path_env);
	return (executable_path);
}

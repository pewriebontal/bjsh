/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:34:58 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 16:42:40 by mkhaing          ###   ########.fr       */
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

char	*construct_executable_path(const char *path, const char *command)
{
	char	*executable_path;

	executable_path = chope(420);
	if (!executable_path)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(executable_path, path);
	ft_strcat(executable_path, "/");
	ft_strcat(executable_path, command);
	return (executable_path);
}

char	*search_in_paths(const char *command, char *path_env)
{
	const char	*path;
	char		*constructed_path;

	path = ft_strtok(path_env, ":");
	while (path)
	{
		constructed_path = construct_executable_path(path, command);
		if (access(constructed_path, X_OK) == 0)
		{
			return (constructed_path);
		}
		yeet(constructed_path);
		path = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_executable(const char *command, char **envp)
{
	char	*executable_path;
	char	*path_env;

	executable_path = check_absolute_or_relative_path(command);
	if (executable_path)
		return (executable_path);
	path_env = get_env_local(envp, "PATH");
	if (!path_env)
		return (NULL);
	executable_path = search_in_paths(command, path_env);
	yeet(path_env);
	return (executable_path);
}

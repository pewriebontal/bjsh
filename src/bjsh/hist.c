/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 16:42:40 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*bjsh_get_history_path(void)
{
	const char	*home;
	char		*path;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	path = chope(ft_strlen(home) + ft_strlen("/.bjsh_history") + 1);
	ft_strcpy(path, home);
	ft_strcat(path, "/.bjsh_history");
	return (path);
}

void	bjsh_hist_file_create(void)
{
	char	*path;
	int		fd_hist;

	path = bjsh_get_history_path();
	fd_hist = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_hist == -1)
	{
		yeet(path);
		return ;
	}
	close(fd_hist);
	yeet(path);
	return ;
}

int	bjsh_read_history(char *path)
{
	char	*line;
	int		fd;
	char	*trimmed_line;

	line = "";
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, " \t\n\r");
		if (trimmed_line && *trimmed_line != '\0')
		{
			add_history(trimmed_line);
		}
		yeet(trimmed_line);
		yeet(line);
	}
	close(fd);
	return (0);
}

int	bjsh_hist_add_entry(char *entry)
{
	char	*path;
	int		fd_hist;

	path = bjsh_get_history_path();
	fd_hist = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_hist == -1)
	{
		yeet(path);
		return (-1);
	}
	ft_dprintf(fd_hist, "%s\n", entry);
	close(fd_hist);
	yeet(path);
	return (0);
}

void	yeet_history_path(t_bjsh *bjsh)
{
	if (bjsh->history_path)
	{
		yeet(bjsh->history_path);
		bjsh->history_path = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/18 18:57:28 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <byamc/gnl.h>
#include <minishell.h>

char	*bjsh_get_history_path(void)
{
	char	*HOME;
	char	*path;

	// get the home directory
	HOME = getenv("HOME");
	// create the path
	path = malloc(strlen(HOME) + strlen("/.bjsh_history") + 1);
	strcpy(path, HOME);
	strcat(path, "/.bjsh_history");
	return (path);
}

/**
 * @brief this function creates a file to store the history
 *
 */
void	bjsh_hist_file_create(void)
{
	char	*path;
	int		fd_hist;

	path = bjsh_get_history_path();
	fd_hist = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	// close the file
	close(fd_hist);
	free(path);
	return ;
}

/**
 * @brief
 *
 * @param line
 */
void	bjsh_hist_file_append(char *line)
{
	char	*path;
	int		fd_hist;

	path = bjsh_get_history_path();
	// open the file
	fd_hist = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	// write the line to the file
	write(fd_hist, line, strlen(line));
	write(fd_hist, "\n", 1);
	// close the file
	close(fd_hist);
	free(path);
	return ;
}

void	bjsh_hist_build(t_bjsh_hist *hist)
{
	char *path;
	path = bjsh_get_history_path();

	// open the file
	int fd_hist;
	fd_hist = open(path, O_RDONLY);

	// read the file
	char *line;
	line = "";

	while (line != NULL)
	{
		line = get_next_line(fd_hist);
		printf("%s\n", line);
		free(line);
	}
	// close the file
	close(fd_hist);
	free(path);

	return ;
}
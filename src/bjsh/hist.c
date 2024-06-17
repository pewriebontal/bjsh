/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 18:39:53 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <byamc/gnl.h>
#include <minishell.h>

char	*bjsh_get_history_path(void)
{
	char	*HOME;
	char	*path;

	HOME = getenv("HOME");
	path = malloc(ft_strlen(HOME) + ft_strlen("/.bjsh_history") + 1);
	ft_strcpy(path, HOME);
	strcat(path, "/.bjsh_history");
	return (path);
}

void	bjsh_hist_file_create(void)
{
	char	*path;
	int		fd_hist;

	path = bjsh_get_history_path();
	fd_hist = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	close(fd_hist);
	free(path);
	return ;
}

int	bjsh_read_history(char *path)
{
}

int	bjsh_write_history(char *path)
{
}
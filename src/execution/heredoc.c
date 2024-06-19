/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:33:57 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 02:36:49 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_until_limiter(t_bjsh *bjsh, int fd_input, int fd_output,
		char *limiter)
{
	char	*line;
	int		size;
	char	*limiter2;

	size = ft_strlen(limiter);
	limiter2 = ft_strjoin(limiter, "\n");
	write(1, "👉 ", sizeof("👉"));
	line = get_next_line(fd_input);
	replace_env_vars(&line, bjsh);
	while (line != NULL)
	{
		if (ft_strncmp(limiter2, line, size + 2) == 0)
		{
			free(line);
			line = NULL;
		}
		else
		{
			ft_putstr_fd(line, fd_output);
			free(line);
			write(1, "👉 ", sizeof("👉"));
			line = get_next_line(fd_input);
			replace_env_vars(&line, bjsh);
		}
	}
	free(limiter2);
}

char	*read_here_doc(t_bjsh *bjsh, char *limiter)
{
	char	pathname[20];
	char	*number;
	int		fd;
	int		i;

	i = 1;
	while (i < 1000)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/heredoc", 20);
		ft_strlcat(pathname, number, 20);
		free(number);
		if (access(pathname, F_OK) == -1)
		{
			fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0600);
			if (fd != -1)
			{
				read_until_limiter(bjsh, STDIN_FILENO, fd, limiter);
				close(fd);
				return (ft_strdup(pathname));
			}
		}
		i++;
	}
	return (NULL);
}

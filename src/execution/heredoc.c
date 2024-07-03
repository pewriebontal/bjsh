/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:33:57 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/03 08:04:58 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_here_doc_fuck_norm(int *size, char **limiter2, const char *limiter)
{
	*size = ft_strlen(limiter);
	*limiter2 = ft_strjoin(limiter, "\n");
}

void	free_line_fuck_norm(char **line)
{
	yeet(*line);
	*line = NULL;
}

void	read_until_limiter(t_bjsh *bjsh, int fd_output, const char *limiter)
{
	char	*line;
	int		size;
	char	*limiter2;

	init_here_doc_fuck_norm(&size, &limiter2, limiter);
	while (1)
	{
		line = readline("👉 ");
		if (!line)
			ft_dprintf(fd_output, "\n");
		if (line)
			replace_env_vars(&line, bjsh);
		if (line == NULL || ft_strncmp(limiter2, line, size) == 0)
		{
			free_line_fuck_norm(&line);
			break ;
		}
		ft_dprintf(fd_output, "%s\n", line);
		yeet(line);
	}
	yeet(limiter2);
}

char	*read_here_doc(t_bjsh *bjsh, const char *limiter)
{
	char	pathname[20];
	char	*number;
	int		fd;
	int		i;

	i = 1;
	while (i < 10000)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/heredoc", 21);
		ft_strlcat(pathname, number, 21);
		yeet(number);
		if (access(pathname, F_OK) == -1)
		{
			fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0600);
			if (fd != -1)
			{
				read_until_limiter(bjsh, fd, limiter);
				close(fd);
				return (ft_strdup(pathname));
			}
		}
		i++;
	}
	return (NULL);
}

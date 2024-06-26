/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:25:41 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 02:08:44 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_input_file(const char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		perror("open");
	}
	return (file_fd);
}

int	read_and_write_file(int file_fd, t_redirection_data *rd)
{
	int	result;

	result = 0;
	rd->bytes_read = read(file_fd, rd->buffer, sizeof(rd->buffer));
	while (rd->bytes_read > 0)
	{
		rd->bytes_written = write(rd->temp_fd, rd->buffer, rd->bytes_read);
		if (rd->bytes_written == -1)
		{
			perror("write");
			result = -1;
			break ;
		}
		rd->bytes_read = read(file_fd, rd->buffer, sizeof(rd->buffer));
	}
	if (rd->bytes_read == -1)
	{
		perror("read");
		result = -1;
	}
	return (result);
}

int	process_current_input_file(const t_exe_context *context,
		t_redirection_data *rd)
{
	int	file_fd;
	int	result;

	file_fd = open_input_file(context->current->str);
	if (file_fd == -1)
	{
		return (-1);
	}
	result = read_and_write_file(file_fd, rd);
	close(file_fd);
	return (result);
}

int	process_input_files(t_exe_context *context, t_redirection_data *rd)
{
	context->current = context->current->next;
	while (context->current != NULL && context->current->type == -1)
	{
		if (process_current_input_file(context, rd) == -1)
		{
			return (-1);
		}
		context->current = context->current->next;
	}
	return (0);
}

int	reopen_temp_file_for_reading(t_exe_context *context)
{
	context->in_fd = open(BJSH_TEMP_FILE, O_RDONLY);
	if (context->in_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

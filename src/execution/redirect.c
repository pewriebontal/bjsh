/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:46:54 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 16:41:53 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirect_out(t_exe_context *context, t_redirection_data *rd)
{
	rd->flags = O_WRONLY | O_CREAT;
	if (context->current->type == REDIRECT_OUT)
		rd->flags |= O_TRUNC;
	else
		rd->flags |= O_APPEND;
	context->out_fd = open(context->current->next->str, rd->flags, 0644);
	if (context->out_fd == -1)
	{
		perror("open");
		return (-1);
	}
	context->current = context->current->next->next;
	return (0);
}

int	open_temp_file(t_redirection_data *rd)
{
	rd->temp_fd = open(BJSH_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (rd->temp_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

int	handle_redirect_in(t_exe_context *context, t_redirection_data *rd)
{
	if (open_temp_file(rd) == -1)
		return (-1);
	if (process_input_files(context, rd) == -1)
		return (-1);
	close(rd->temp_fd);
	if (reopen_temp_file_for_reading(context) == -1)
		return (-1);
	return (0);
}

int	handle_redirect_in_here(t_exe_context *context,
		t_redirection_data *rd, t_bjsh *bjsh)
{
	context->current = context->current->next;
	rd->heredoc_file = read_here_doc(bjsh, context->current->str);
	if (rd->heredoc_file == NULL)
	{
		ft_dprintf(2, "🤌 ❯ failed to read heredoc\n");
		return (-1);
	}
	context->in_fd = open(rd->heredoc_file, O_RDONLY);
	if (context->in_fd == -1)
	{
		perror("open");
		return (-1);
	}
	yeet(rd->heredoc_file);
	context->current = context->current->next;
	return (0);
}

// Function to handle redirections before executing commands
int	handle_redirections(t_exe_context *context, t_bjsh *bjsh)
{
	t_redirection_data	rd;

	while (context->current != NULL && (context->current->type == REDIRECT_OUT
			|| context->current->type == REDIRECT_OUT_APPEND
			|| context->current->type == REDIRECT_IN
			|| context->current->type == REDIRECT_IN_HERE))
	{
		if (check_invalid_redirect_sequence(context) == -1)
			return (-1);
		if (context->current->type == REDIRECT_OUT
			|| context->current->type == REDIRECT_OUT_APPEND)
		{
			return (handle_redirect_out(context, &rd));
		}
		else if (context->current->type == REDIRECT_IN)
			return (handle_redirect_in(context, &rd));
		else if (context->current->type == REDIRECT_IN_HERE)
			return (handle_redirect_in_here(context, &rd, bjsh));
	}
	return (0);
}

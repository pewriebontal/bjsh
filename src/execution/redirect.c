/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:46:54 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/23 18:26:50 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to handle redirections before executing commands
int handle_redirections(t_token **current, int *in_fd, int *out_fd, t_bjsh *bjsh)
{
	int flags;
	char *heredoc_file;
	int temp_fd;
	char buffer[1024];
	ssize_t bytes_read;
	ssize_t bytes_written;

	while (*current != NULL && ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND || (*current)->type == REDIRECT_IN || (*current)->type == REDIRECT_IN_HERE))
	{
		// Check for invalid sequences of redirection tokens
		if ((*current)->next == NULL)
		{
			// No token after the redirection operator
			ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n",
					   (*current)->str);
			return (-1);
		}
		else if ((*current)->next->type == REDIRECT_OUT || (*current)->next->type == REDIRECT_OUT_APPEND || (*current)->next->type == REDIRECT_IN || (*current)->next->type == REDIRECT_IN_HERE)
		{
			// Redirection operator followed by another redirection operator
			ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n",
					   (*current)->next->str);
			// Move past the erroneous token to avoid repeated error messages
			*current = (*current)->next;
			return (-1);
		}
		if ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND)
		{
			flags = O_WRONLY | O_CREAT;
			flags |= ((*current)->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
			*out_fd = open((*current)->next->str, flags, 0644);
			if (*out_fd == -1)
			{
				perror("open");
				return (-1);
			}
			*current = (*current)->next->next;
		}
		else if ((*current)->type == REDIRECT_IN)
		{
			// Create a temporary file to concatenate the contents
			temp_fd = open(BJSH_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (temp_fd == -1)
			{
				perror("open");
				return (-1);
			}

			// Process each file specified after the < redirection
			*current = (*current)->next; // Move to the file name token
			while (*current != NULL && (*current)->type == -1)
			{
				int file_fd = open((*current)->str, O_RDONLY);
				if (file_fd == -1)
				{
					perror("open");
					return (-1);
				}

				// Read from the file and write to the temporary file
				while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0)
				{
					bytes_written = write(temp_fd, buffer, bytes_read);
					if (bytes_written == -1)
					{
						perror("write");
						return (-1);
					}
				}

				close(file_fd);
				*current = (*current)->next;
			}

			// Close the temporary file descriptor after writing
			close(temp_fd);

			// Reopen the temporary file for reading
			*in_fd = open(BJSH_TEMP_FILE, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				return (-1);
			}
		}
		else if ((*current)->type == REDIRECT_IN_HERE)
		{
			// Move to the heredoc delimiter token
			*current = (*current)->next;
			heredoc_file = read_here_doc(bjsh, (*current)->str);
			if (heredoc_file == NULL)
			{
				ft_dprintf(2, "🤌 ❯ failed to read heredoc\n");
				return (-1);
			}
			*in_fd = open(heredoc_file, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				return (-1);
			}
			free(heredoc_file);
			*current = (*current)->next;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:46:54 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/23 16:40:18 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to handle redirections before executing commands
int handle_redirections(t_token **current, int *in_fd, int *out_fd, t_bjsh *bjsh)
{
	while (*current != NULL && ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND ||
								(*current)->type == REDIRECT_IN || (*current)->type == REDIRECT_IN_HERE))
	{
		// Check for invalid sequences of redirection tokens
		if ((*current)->next == NULL)
		{
			// No token after the redirection operator
			ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n", (*current)->str);
			return -1;
		}
		else if ((*current)->next->type == REDIRECT_OUT || (*current)->next->type == REDIRECT_OUT_APPEND ||
				 (*current)->next->type == REDIRECT_IN || (*current)->next->type == REDIRECT_IN_HERE)
		{
			// Redirection operator followed by another redirection operator
			ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n", (*current)->next->str);
			// Move past the erroneous token to avoid repeated error messages
			*current = (*current)->next;
			return -1;
		}

		if ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND)
		{
			int flags = O_WRONLY | O_CREAT;
			flags |= ((*current)->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
			*out_fd = open((*current)->next->str, flags, 0644);
			if (*out_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if ((*current)->type == REDIRECT_IN)
		{
			*in_fd = open((*current)->next->str, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if ((*current)->type == REDIRECT_IN_HERE)
		{
			char *heredoc_file = read_here_doc(bjsh, (*current)->next->str);
			if (heredoc_file == NULL)
			{
				ft_dprintf(2, "Failed to create heredoc file\n");
				exit(EXIT_FAILURE);
			}
			*in_fd = open(heredoc_file, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			free(heredoc_file);
		}
		*current = (*current)->next->next; // Move past the redirection token and its target
	}
	return 0;
}

// Function to handle redirections before executing commands
void handle_redirections3(t_token **current, int *in_fd, int *out_fd,
						 t_bjsh *bjsh)
{
	int flags;
	char *heredoc_file;

	while (*current != NULL && ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND || (*current)->type == REDIRECT_IN || (*current)->type == REDIRECT_IN_HERE))
	{
		// Check for invalid sequences of redirection tokens
		if ((*current)->next != NULL && ((*current)->next->type == REDIRECT_OUT || (*current)->next->type == REDIRECT_OUT_APPEND || (*current)->next->type == REDIRECT_IN || (*current)->next->type == REDIRECT_IN_HERE))
		{
			ft_dprintf(2, "bjsh: syntax error near unexpected token `%s'\n",
					(*current)->next->str);
			return;
		}
		if ((*current)->type == REDIRECT_OUT || (*current)->type == REDIRECT_OUT_APPEND)
		{
			flags = O_WRONLY | O_CREAT;
			flags |= ((*current)->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
			*out_fd = open((*current)->next->str, flags, 0644);
			if (*out_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if ((*current)->type == REDIRECT_IN)
		{
			*in_fd = open((*current)->next->str, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if ((*current)->type == REDIRECT_IN_HERE)
		{
			heredoc_file = read_here_doc(bjsh, (*current)->next->str);
			if (heredoc_file == NULL)
			{
				ft_dprintf(2, "Failed to create heredoc file\n");
				exit(EXIT_FAILURE);
			}
			*in_fd = open(heredoc_file, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			free(heredoc_file);
		}
		*current = (*current)->next->next;
		// Move past the redirection token and its target
	}
}

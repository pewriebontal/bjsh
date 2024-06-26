/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exehandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:32:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 02:08:44 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to handle input/output redirection
void	handle_io_redirection(t_exe_context *context)
{
	dup2(context->in_fd, STDIN_FILENO);
	if (context->out_fd != STDOUT_FILENO)
		dup2(context->out_fd, STDOUT_FILENO);
	else if (context->current != NULL)
		dup2(context->fd[1], STDOUT_FILENO);
	if (context->in_fd != STDIN_FILENO)
		close(context->in_fd);
	if (context->out_fd != STDOUT_FILENO)
		close(context->out_fd);
	if (context->current != NULL)
		close(context->fd[0]);
}

// Function to handle child process execution
void	handle_child_process(char *args[], t_exe_context *context,
		t_bjsh *bjsh)
{
	handle_io_redirection(context);
	execute_builtin_g(args, bjsh);
	execute_command4(args, bjsh->envp);
}

// Function to handle parent process execution
void	handle_parent_process(t_exe_context *context, t_bjsh *bjsh)
{
	wait(&context->status);
	if (WIFEXITED(context->status))
		bjsh->last_exit_status = WEXITSTATUS(context->status);
	else if (WIFSIGNALED(context->status))
		bjsh->last_exit_status = 128 + WTERMSIG(context->status);
}

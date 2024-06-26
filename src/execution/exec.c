/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 02:08:44 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to execute a single command using execve
void	execute_command4(char **args, char **envp)
{
	char	*path;

	path = find_executable(args[0], envp);
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "🤌 ❯ command not found: %s\n", args[0]);
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

// Function to initialize the execution context
void	initialize_execution_context(t_exe_context *context,
		t_token *head)
{
	context->current = head;
	context->in_fd = STDIN_FILENO;
	context->out_fd = STDOUT_FILENO;
	context->command_found = find_command(context->current);
}

// Function to handle the execution of a single command
int	execute_single_command(char *args[], t_exe_context *context,
		t_bjsh *bjsh)
{
	if (check_builtin(args[0]) == BUGGI_BAKA)
	{
		bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		return (0);
	}
	else if (context->current == NULL || context->current->type == PIPE)
	{
		if (context->current != NULL)
			pipe(context->fd);
		execute_command_or_builtin(args, context, bjsh);
		if (context->current != NULL)
		{
			close(context->fd[1]);
			context->in_fd = context->fd[0];
			context->current = context->current->next;
		}
		return (0);
	}
	return (1);
}

// Function to handle the execution loop
void	execute_loop(t_exe_context *context, t_bjsh *bjsh)
{
	char	*args[MAX_ARGS];

	while (context->current != NULL)
	{
		context->argc = 0;
		collect_arguments(&context->current, args, &context->argc);
		if (handle_redirections(context, bjsh) == -1)
			return ;
		if (!execute_single_command(args, context, bjsh))
			continue ;
		context->current = context->current->next;
	}
}

// Main function to handle command execution
void	execute_tokens(t_token *head, t_bjsh *bjsh)
{
	t_exe_context	context;

	if (head == NULL)
		return ;
	if (check_invalid_pipe_sequence(head))
	{
		bjsh->last_exit_status = 2;
		return ;
	}
	initialize_execution_context(&context, head);
	if (!context.command_found)
	{
		ft_dprintf(STDERR_FILENO,
			"🤌 ❯ syntax error near unexpected token `newline'\n");
		bjsh->last_exit_status = 2;
		return ;
	}
	execute_loop(&context, bjsh);
	if (context.in_fd != STDIN_FILENO)
		close(context.in_fd);
	if (context.out_fd != STDOUT_FILENO)
		close(context.out_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/23 22:47:34 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

// Function to execute a single command using execve
void execute_command4(char **args, char **envp)
{
	char *path;

	path = find_executable(args[0], envp);
	if (path == NULL)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void execute_tokens(t_token *head, t_bjsh *bjsh)
{
	if (head == NULL)
        return;
	t_execution_context context;
	context.current = head;
	context.in_fd = STDIN_FILENO;	// Initially, input comes from standard input
	context.out_fd = STDOUT_FILENO; // Initially, output goes to standard output
	context.command_found = find_command(context.current);

 	// If no commands are found, return without executing anything
	if (!context.command_found)
	{
		ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `newline'\n");
		return;
	}

	// Reset current to head to start execution
	context.current = head;
	while (context.current != NULL)
	{
		char *args[MAX_ARGS]; // Assuming no command has more than 100 arguments
		context.argc = 0;
		// Collect arguments for the current command
		collect_arguments(&context.current, args, &context.argc);

		// Handle redirections before executing commands
		if (handle_redirections(&context, bjsh) == -1)
		{
			// If there's a redirection error, return immediately without executing
			return;
		}

		if (check_builtin(args[0]) == BUGGI_BAKA)
		{
			bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		}
		else if (context.current == NULL || context.current->type == PIPE)
		{
			// If we reach a pipe or the end of the chain, execute the command
			if (context.current != NULL)
				pipe(context.fd);
			execute_command_or_builtin(args, &context, bjsh);
			if (context.current != NULL)
			{
				close(context.fd[1]);
				context.in_fd = context.fd[0]; // Save the input for the next command
				context.current = context.current->next;
			}
		}
		else
		{
			// If we encounter an unsupported token type, just skip it
			context.current = context.current->next;
		}
	}

	// Close any remaining open file descriptors
	if (context.in_fd != STDIN_FILENO)
		close(context.in_fd);
	if (context.out_fd != STDOUT_FILENO)
		close(context.out_fd);
}

// Function to find if there's any command to execute
int find_command(t_token *current)
{
	while (current != NULL)
	{
		if (current->type == -1)
			return (1);
		current = current->next;
	}
	return (0);
}

// Function to collect arguments for the current command
void collect_arguments(t_token **current, char *args[], int *argc)
{
	while (*current != NULL && (*current)->type == -1)
	{
		args[(*argc)++] = (*current)->str;
		*current = (*current)->next;
	}
	args[*argc] = NULL; // Null-terminate the arguments array
}

// Function to execute a command or builtin
void execute_command_or_builtin(char *args[], t_execution_context *context, t_bjsh *bjsh)
{
	if (fork() == 0)
	{
		dup2(context->in_fd, STDIN_FILENO); // Change the input to the previous output
		if (context->out_fd != STDOUT_FILENO)
			dup2(context->out_fd, STDOUT_FILENO); // Set the output if redirected
		else if (context->current != NULL)
			dup2(context->fd[1], STDOUT_FILENO); // Set the output to the pipe
		if (context->in_fd != STDIN_FILENO)
			close(context->in_fd);
		if (context->out_fd != STDOUT_FILENO)
			close(context->out_fd);
		if (context->current != NULL)
			close(context->fd[0]);
		if (check_builtin(args[0]) == SUSSY_BAKA)
		{
			bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
			exit(bjsh->last_exit_status);
		}
		else
			execute_command4(args, bjsh->envp);
	}
	else
	{
		wait(&context->status);
		if (WIFEXITED(context->status))
			bjsh->last_exit_status = WEXITSTATUS(context->status);
		else if (WIFSIGNALED(context->status))
			bjsh->last_exit_status = 128 + WTERMSIG(context->status);
	}
}
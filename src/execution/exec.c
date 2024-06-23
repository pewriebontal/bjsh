/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/23 16:43:19 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

// Function to execute a single command using execve
void execute_command4(char **args, char **envp)
{
	char *path = find_executable(args[0], envp);
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

// Function to handle the execution of the t_token chain
void execute_tokens(t_token *head, t_bjsh *bjsh)
{
	t_token *current = head;
	int fd[2];
	int in_fd = STDIN_FILENO;	// Initially, input comes from standard input
	int out_fd = STDOUT_FILENO; // Initially, output goes to standard output
	int status;
	int command_found = find_command(current);

	// If no commands are found, return without executing anything
	if (!command_found)
	{
		ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `newline'\n");
		return;
	}
	// Reset current to head to start execution
	current = head;

	while (current != NULL)
	{
		char *args[MAX_ARGS]; // Assuming no command has more than 100 arguments
		int argc = 0;

		// Collect arguments for the current command
		collect_arguments(&current, args, &argc);
		// Handle redirections before executing commands
		if (handle_redirections(&current, &in_fd, &out_fd, bjsh) == -1)
		{
			// If there's a redirection error, return immediately without executing
			return;
		}

		if (check_builtin(args[0]) == BUGGI_BAKA)
			bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		else if (current == NULL || current->type == PIPE)
		{
			// If we reach a pipe or the end of the chain, execute the command
			if (current != NULL)
				pipe(fd);
			execute_command_or_builtin(args, current, in_fd, out_fd, fd, bjsh);

			if (current != NULL)
			{
				close(fd[1]);
				in_fd = fd[0]; // Save the input for the next command
				current = current->next;
			}
		}
		else
			// If we encounter an unsupported token type, just skip it
			current = current->next;
	}

	// Close any remaining open file descriptors
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

// Function to find if there's any command to execute
int find_command(t_token *current)
{
	while (current != NULL)
	{
		if (current->type == -1)
			return 1;
		current = current->next;
	}
	return 0;
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
void execute_command_or_builtin(char *args[], t_token *current, int in_fd, int out_fd, int *fd, t_bjsh *bjsh)
{
	int status;
	if (fork() == 0)
	{
		dup2(in_fd, STDIN_FILENO); // Change the input to the previous output
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO); // Set the output if redirected
		else if (current != NULL)
			dup2(fd[1], STDOUT_FILENO); // Set the output to the pipe
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		if (current != NULL)
			close(fd[0]);

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
		wait(&status);
		if (WIFEXITED(status))
			bjsh->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			bjsh->last_exit_status = 128 + WTERMSIG(status);
	}
}

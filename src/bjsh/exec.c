/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/18 18:45:41 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

char *resolve_path(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char full_path[1024];

	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			return strdup(full_path);
		}
		token = strtok(NULL, ":");
	}
	return NULL;
}

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
	int in_fd = 0; // Initially, input comes from standard input
	int status;

	while (current != NULL)
	{
		char *args[100]; // Assuming no command has more than 100 arguments
		int argc = 0;

		// Collect arguments for the current command
		while (current != NULL && current->type == -1)
		{
			args[argc++] = current->str;
			current = current->next;
		}
		args[argc] = NULL; // Null-terminate the arguments array

		if (check_builtin(args[0]) == BUGGI_BAKA)
		{
			bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		}
		else if (current == NULL || current->type == PIPE)
		{
			// If we reach a pipe or the end of the chain, execute the command
			pipe(fd);

			if (fork() == 0)
			{
				dup2(in_fd, 0); // Change the input to the previous output
				if (current != NULL)
				{
					dup2(fd[1], 1); // Set the output to the pipe
				}
				close(fd[0]);
				if (check_builtin(args[0]) == SUSSY_BAKA)
				{
					bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
					exit(bjsh->last_exit_status);
				}
				else
				{
					execute_command4(args, bjsh->envp);
				}
			}
			else
			{
				wait(&status);
				if (WIFEXITED(status))
				{
					bjsh->last_exit_status = WEXITSTATUS(status);
				}
				else if (WIFSIGNALED(status))
				{
					bjsh->last_exit_status = 128 + WTERMSIG(status);
				}
				close(fd[1]);
				in_fd = fd[0]; // Save the input for the next command
				if (current != NULL)
				{
					current = current->next;
				}
			}
		}
		else if (current->type == REDIRECT_OUT || current->type == REDIRECT_OUT_APPEND)
		{
			int flags = O_WRONLY | O_CREAT;
			flags |= (current->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
			int out_fd = open(current->next->str, flags, 0644);
			if (out_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}

			if (fork() == 0)
			{
				dup2(in_fd, 0);
				dup2(out_fd, 1);
				close(out_fd);
				if (check_builtin(args[0]) == SUSSY_BAKA)
				{
					bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
					exit(bjsh->last_exit_status);
				}
				else
				{
					execute_command4(args, bjsh->envp);
				}
			}
			else
			{
				wait(&status);
				if (WIFEXITED(status))
				{
					bjsh->last_exit_status = WEXITSTATUS(status);
				}
				else if (WIFSIGNALED(status))
				{
					bjsh->last_exit_status = 128 + WTERMSIG(status);
				}
				close(out_fd);
				if (current->next != NULL)
				{
					current = current->next->next;
				}
			}
		}
		else if (current->type == REDIRECT_IN)
		{
			int in_fd = open(current->next->str, O_RDONLY);
			if (in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}

			if (fork() == 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
				if (check_builtin(args[0]) == SUSSY_BAKA)
				{
					bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
					exit(bjsh->last_exit_status);
				}
				else
				{
					execute_command4(args, bjsh->envp);
				}
			}
			else
			{
				wait(&status);
				if (WIFEXITED(status))
				{
					bjsh->last_exit_status = WEXITSTATUS(status);
				}
				else if (WIFSIGNALED(status))
				{
					bjsh->last_exit_status = 128 + WTERMSIG(status);
				}
				close(in_fd);
				if (current->next != NULL)
				{
					current = current->next->next;
				}
			}
		}
		else
		{
			// If we encounter an unsupported token type, just skip it
			current = current->next;
		}
	}
}
// int	find_executable(char *command, char *path_buffer)
//{
//	char		*path_env;
//	char		*start;
//	size_t		remaining_size;
//	char		*end;
//	struct stat	statbuf;
//	size_t		path_buffer_size;
//
//	path_buffer_size = 1024;
//	path_env = getenv("PATH");
//	start = path_env;
//	remaining_size = path_buffer_size;
//	if (!path_env)
//		return (0);
//	while (start)
//	{
//		end = ft_strchr(start, ':');
//		if (!end)
//			end = start + ft_strlen(start); //??
//		// Check if there's enough space in the buffer
//		if (end - start + 1 + ft_strlen(command) + 1 > remaining_size)
//		{
//			// Handle buffer overflow (e.g., return an error code)
//			return (-1);
//		}
//		// Copy directory path
//		ft_strncpy(path_buffer, start, end - start);
//		path_buffer[end - start] = '\0';
//		// Construct full path
//		ft_strlcat(path_buffer, "/", remaining_size);
//		ft_strlcat(path_buffer, command, remaining_size);
//		if (stat(path_buffer, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
//			return (1);
//		start = (*end) ? end + 1 : NULL;
//		remaining_size -= end - start + 1; // Update remaining buffer size
//	}
//	return (0);
//}

// need rewrite with allowed functions
int find_executable2(char *command, char *path_buffer)
{
	char *path_env;
	char *path;
	char *dir;
	struct stat statbuf;

	path_env = getenv("PATH");
	if (!path_env)
		return (0);
	path = ft_strdup(path_env);
	dir = strtok(path, ":");
	while (dir != NULL)
	{
		sprintf(path_buffer, "%s/%s", dir, command);
		if (stat(path_buffer, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
		{
			free(path);
			return (1);
		}
		dir = strtok(NULL, ":");
	}
	free(path);
	return (0);
}

// int	bjsh_exec(char **args, t_bjsh *bjsh)
//{
//	pid_t	pid;
//	int		status;
//	char	path[1024];
//	char	*cmd;
//
//	execve_pipe(bjsh); //!!!test!!!
//	// set_token_list(bjsh);//!!!test!!!
//	if (!find_executable(args[0], path))
//	{
//		display_error_msg("command not found: ");
//		ft_putendl_fd(args[0], STDERR_FILENO);
//		return (127); // Return 127 for command not found
//	}
//	// wpid
//	pid = fork();
//	if (pid == 0)
//	{
//		// handle_redirections(args);
//		// handle_pipes(args, bjsh);
//		if (execve(path, args, bjsh->envp) == -1)
//		{
//			ft_printf("🍦bjsh👎 command not found: %s\n", args[0]);
//			exit(126);
//		}
//	}
//	else if (pid > 0)
//	{
//		waitpid(pid, &status, 0);
//		if (WIFEXITED(status))
//			return (WEXITSTATUS(status));
//		else if (WIFSIGNALED(status))
//			return (128 + WTERMSIG(status));
//	}
//	else
//	{
//		perror("minishell: fork");
//		return (1); // Return a general error code
//	}
// }

int exec_cmd(t_bjsh *bjsh, int type)
{
}
//{
//	if (type == PIPE || type == END)
//	{
//		bjsh_exec(bjsh->argv, bjsh);
//	}
//	if (type == RDIR_R)
//	{
//		// redirect right
//	}
//	if (type == RDIR_RR)
//	{
//		// redirect right
//	}
//	if (type == RDIR_L)
//	{
//		// redirect left
//	}
//}

// int	execute_tokens(t_bjsh *bjsh, t_token *token)
//{
//	while (token)
//	{
//		if (token->type == 1)
//		{
//			pre_execute(token->str, bjsh);
//		}
//		token = token->next;
//	}
//}
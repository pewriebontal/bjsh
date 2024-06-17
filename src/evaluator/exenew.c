#include <fcntl.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Main execution function
void	execute_tokens1(t_token *tokens, char **envp)
{
	t_token	*current;
	t_token	*command_start;

	current = tokens;
	command_start = current;
	while (current)
	{
		if (current->type == PIPE)
		{
			current->str = NULL;
			handle_pipes(command_start, envp);
			command_start = current->next;
		}
		else if (current->type == REDIRECT_OUT
			|| current->type == REDIRECT_OUT_APPEND
			|| current->type == REDIRECT_IN)
		{
			handle_redirection(&current);
		}
		current = current->next;
	}
	if (command_start)
	{
		execute_command(command_start, envp);
	}
}

// Function to execute a single command
void	execute_command(t_token *tokens, char **envp)
{
	char	*args[256];
	int		i;
	char	*executable_path;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		args[i++] = tokens->str;
		tokens = tokens->next;
	}
	args[i] = NULL;
	if (check_builtin(args[0]))
	{
		bjsh_exec_builtin(args);
		return ;
	}
	executable_path = find_executable(args[0], envp);
	if (fork() == 0)
	{
		if (executable_path)
		{
			execve(executable_path, args, envp);
			perror("execve failed");
			exit(1);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
	free(executable_path);
}

// Function to handle redirection
void	handle_redirection(t_token **tokens)
{
	t_token	*current;
	int		fd;

	current = *tokens;
	if (current->type == REDIRECT_OUT_APPEND)
	{
		fd = open(current->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (current->type == REDIRECT_OUT)
	{
		fd = open(current->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (current->type == REDIRECT_IN)
	{
		fd = open(current->next->str, O_RDONLY);
	}
	else
	{
		return ;
	}
	if (fd < 0)
	{
		perror("open failed");
		exit(1);
	}
	if (current->type == REDIRECT_OUT || current->type == REDIRECT_OUT_APPEND)
	{
		dup2(fd, STDOUT_FILENO);
	}
	else if (current->type == REDIRECT_IN)
	{
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	*tokens = current->next->next;
}

// Function to handle pipes
void	handle_pipes(t_token *tokens, char **envp)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_command(tokens, envp);
		exit(1);
	}
	else
	{
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

// Function to find the full path of an executable
char	*find_executable(const char *command, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*path;
	char	*executable_path;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = strdup(path_env);
	path = strtok(paths, ":");
	executable_path = malloc(256);
	while (path)
	{
		snprintf(executable_path, 256, "%s/%s", path, command);
		if (access(executable_path, X_OK) == 0)
		{
			free(paths);
			return (executable_path);
		}
		path = strtok(NULL, ":");
	}
	free(paths);
	free(executable_path);
	return (NULL);
}

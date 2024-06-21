/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exenew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:06:21 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/21 20:03:57 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

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

char	*find_executable(const char *command, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*path;
	char	*executable_path;

	// Check if the command is an absolute or relative path
	if (command[0] == '/' || (command[0] == '.' && (command[1] == '/' || command[1] == '.')))
	{
		if (access(command, X_OK) == 0)
			return ft_strdup(command);
		return NULL;
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_strdup(path_env);
	path = ft_strtok(paths, ":");
	executable_path = malloc(256);
	while (path)
	{
		snprintf(executable_path, 256, "%s/%s", path, command);
		if (access(executable_path, X_OK) == 0)
		{
			free(paths);
			return (executable_path);
		}
		path = ft_strtok(NULL, ":");
	}
	free(paths);
	free(executable_path);
	return (NULL);
}

// Function to find the full path of an executable
char	*find_executable44(const char *command, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*path;
	char	*executable_path;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_strdup(path_env);
	path = ft_strtok(paths, ":");
	executable_path = malloc(256);
	while (path)
	{
		snprintf(executable_path, 256, "%s/%s", path, command);
		if (access(executable_path, X_OK) == 0)
		{
			free(paths);
			return (executable_path);
		}
		path = ft_strtok(NULL, ":");
	}
	free(paths);
	free(executable_path);
	return (NULL);
}

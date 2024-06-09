/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/05 00:21:50 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

int	find_executable(char *command, char *path_buffer)
{
	char		*path_env;
	char		*start;
	size_t		remaining_size;
	char		*end;
	struct stat	statbuf;
	size_t		path_buffer_size;

	path_buffer_size = 1024;
	path_env = getenv("PATH");
	start = path_env;
	remaining_size = path_buffer_size;
	if (!path_env)
		return (0);
	while (start)
	{
		end = ft_strchr(start, ':');
		if (!end)
			end = start + ft_strlen(start);//??
		// Check if there's enough space in the buffer
		if (end - start + 1 + ft_strlen(command) + 1 > remaining_size)
		{
			// Handle buffer overflow (e.g., return an error code)
			return (-1);
		}
		// Copy directory path
		ft_strncpy(path_buffer, start, end - start);
		path_buffer[end - start] = '\0';
		// Construct full path
		ft_strlcat(path_buffer, "/", remaining_size);
		ft_strlcat(path_buffer, command, remaining_size);
		if (stat(path_buffer, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
			return (1);
		start = (*end) ? end + 1 : NULL;
		remaining_size -= end - start + 1; // Update remaining buffer size
	}
	return (0);
}

// need rewrite with allowed functions
int	find_executable2(char *command, char *path_buffer)
{
	char		*path_env;
	char		*path;
	char		*dir;
	struct stat	statbuf;

	path_env = getenv("PATH");
	if (!path_env)
		return (0);
	path = strdup(path_env);
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

int	bjsh_exec(char **args, t_bjsh *bjsh)
{
	pid_t	pid;
	int		status;
	char	path[1024];
	char	*cmd;

	execve_pipe(bjsh);//!!!test!!!
	//set_token_list(bjsh);//!!!test!!!
	
	if (!find_executable(args[0], path))
	{
		display_error_msg("command not found: ");
		ft_putendl_fd(args[0], STDERR_FILENO);
		return (127); // Return 127 for command not found
	}
	// wpid
	pid = fork();
	if (pid == 0)
	{
		// handle_redirections(args);
		// handle_pipes(args, bjsh);
		if (execve(path, args, bjsh->env) == -1)
		{
			ft_printf("🍦bjsh👎 command not found: %s\n", args[0]);
			exit(126);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	else
	{
		perror("minishell: fork");
		return (1); // Return a general error code
	}
}

int	exec_cmd(t_bjsh *bjsh, int type)
{
	if (type == PIPE || type == END)
	{
		bjsh_exec(bjsh->argv, bjsh);
	}
	if (type == RDIR_R)
	{
		// redirect right
	}
	if (type == RDIR_RR)
	{
		// redirect right
	}
	if (type == RDIR_L)
	{
		// redirect left
	}
}
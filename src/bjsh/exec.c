/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/04 23:59:56 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

// need rewrite with allowed functions
int	find_executable(char *command, char *path_buffer)
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

	if (!find_executable(args[0], path))
	{
		perror("minishell");
		display_error_msg("cannot find executable: ");
		return (1);
	}
	// wpid
	pid = fork();
	if (pid < 0)
	{
		ft_printf("🍦bjsh👎: fork failed\n");
	}
	if (pid == 0)
	{
		// handle_redirections(args);
		// handle_pipes(args, bjsh);
		if (execve(path, args, bjsh->env) == -1)
		{
			ft_printf("🍦bjsh👎 command not found: %s\n", args[0]);
		}
		exit(BUSTED);
	}
	waitpid(pid, &status, 0);
	return (UNDERSTOOD_THE_ASSIGNMENT);
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
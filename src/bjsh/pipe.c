/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:05:42 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/11 16:46:42 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// check -1 and perror
void	check_perr(char *a, int p)
{
	if (p < 0)
	{
		if (ft_strcmp(a, "pipe"))
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(a, "pid_left"))
		{
			perror("pid_left");
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(a, "pid_right"))
		{
			perror("pid_right");
			exit(EXIT_FAILURE);
		}
	}
}

void	execve_pipe(t_bjsh *bjsh)
{
	//	int	pid_left;
	//	int	pid_right;
	//	int	fd[2];
	//		char *argc[] = {"ls", NULL};
	//		char *envp[] = {NULL};
	//		char *argc[] = {"wc", NULL};
	//		char *envp[] = {NULL};
	//
	//	check_perr("pipe", pipe(fd)); // havn't tested
	//	pid_left = fork();
	//	check_perr("pid_left", pid_left);
	//	if (pid_left == 0)
	//	{
	//		close(fd[0]);
	//		dup2(fd[1], STDIN_FILENO);
	//		close(fd[1]);
	//		// tmp
	//		execve("/bin/ls", argc, envp);
	//		perror("execve for ls");
	//		exit(EXIT_FAILURE);
	//	}
	//	pid_right = fork();
	//	check_perr("pid_right", pid_right);
	//	if (pid_right == 0)
	//	{
	//		close(fd[1]);
	//		dup2(fd[0], STDIN_FILENO);
	//		close(fd[0]);
	//		// tmp
	//		execve("/bin/wc", argc, envp);
	//		perror("execve for grep");
	//		exit(EXIT_FAILURE);
	//	}
	//	close(fd[0]);
	//	close(fd[1]);
	//	waitpid(pid_left, NULL, 0);
	//	waitpid(pid_right, NULL, 0);
}

void	execute_pipe(t_bjsh *bjsh, char *cmd1, char *cmd2)
{
	int pipefd[2];
	int pid;

	/// pipes [0] is for reading, pipes [1] is for writing
	/// dup2 is used to copy file descriptors
	/// close is used to close file descriptors

	pipe(pipefd);

	pid = fork();

	if (pid == 0) // child
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execvp(cmd1, NULL);
		// execve_pipe2(bjsh);
		// execve(find_executable(args[0], bjsh->env), args, bjsh->env);
	}
	else // parent
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execvp(cmd2, NULL);
		// execlp(find_executable(args[1], bjsh->env), args[1], NULL);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
}
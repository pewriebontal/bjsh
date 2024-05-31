/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jason <jason@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/31 20:36:19 by jason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

int	bjsh_exec(char **args)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	*cmd;

	// wpid
	pid = fork();
	if (pid < 0)
	{
		ft_printf("🍦bjsh👎: fork failed\n");
	}
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			ft_printf("🍦bjsh👎 command not found: %s\n", args[0]);
		}
		exit(BUSTED);
	}
	waitpid(pid, &status, 0);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int exec_redir_r(t_bjsh *bjsh)
{
	int fd;
	int status;
	pid_t pid;


	pid = fork();
	if (pid < 0)
	{
		ft_printf("🍦bjsh👎: fork failed\n");
	}
	if (pid == 0)
	{
		fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_printf("🍦bjsh👎: open failed\n");
		}
		dup2(fd, 1);
		close(fd);
		if (execvp(bjsh->argv, bjsh->argv) == -1)
		{
			ft_printf("🍦bjsh👎 command not found: %s\n", bjsh->argv);
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
		bjsh_exec(bjsh->argv);
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
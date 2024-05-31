/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/31 19:22:26 by mkhaing          ###   ########.fr       */
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
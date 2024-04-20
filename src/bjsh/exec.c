/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:16:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/20 22:40:13 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>

int	bjsh_exec(char **args)
{
	pid_t	pid;

	// wpid
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			spill_the_tea("🍦bjsh👎: %s: command not found\n", args[0]);
		}
		exit(BUSTED);
	}
	else if (pid < 0)
	{
		spill_the_tea("🍦bjsh👎: fork failed\n");
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

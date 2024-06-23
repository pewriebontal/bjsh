/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:11:41 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 00:33:23 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to find if there's any command to execute
int	find_command(t_token *current)
{
	while (current != NULL)
	{
		if (current->type == -1)
			return (1);
		current = current->next;
	}
	return (0);
}

// Function to collect arguments for the current command
void	collect_arguments(t_token **current, char *args[], int *argc)
{
	while (*current != NULL && (*current)->type == -1)
	{
		args[(*argc)++] = (*current)->str;
		*current = (*current)->next;
	}
	args[*argc] = NULL;
}

// Function to execute a builtin command
void	execute_builtin_g(char *args[], t_bjsh *bjsh)
{
	if (check_builtin(args[0]) == SUSSY_BAKA)
	{
		bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		exit(bjsh->last_exit_status);
	}
}

// Function to execute a command or builtin
void	execute_command_or_builtin(char *args[], t_execution_context *context,
		t_bjsh *bjsh)
{
	if (fork() == 0)
		handle_child_process(args, context, bjsh);
	else
		handle_parent_process(context, bjsh);
}

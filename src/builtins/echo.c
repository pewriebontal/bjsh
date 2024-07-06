/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:03:38 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/06 23:03:39 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_n_option(const char *arg)
{
	int	j;

	j = 1;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	handle_n_options(char **args, int *newline_flag)
{
	int	i;

	i = 1;
	*newline_flag = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (!is_n_option(args[i]))
			break ;
		*newline_flag = 0;
		i++;
	}
	return (i);
}

static void	print_arguments(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	bjsh_echo(char **args)
{
	int	newline_flag;
	int	start_index;

	start_index = handle_n_options(args, &newline_flag);
	print_arguments(args, start_index);
	if (newline_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

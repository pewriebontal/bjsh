/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/23 13:49:36 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_bjsh(t_bjsh *bjsh)
{
	bjsh->status = CHILLING;
	// create the history file
	bjsh_hist_file_create();
	// bjsh_hist_build();
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	main(int argc, char *argv[])
{
	t_bjsh	bjsh;

	// --version
	// if ./bjsh --version then print version and exit
	// only implemented for neofetch haha
	if (argc == 2 && ft_strncmp(argv[1], "--version", 10) == 0)
	{
		ft_putstr_fd("bjsh (Bon & Jason shell) [development build]\n", 1);
		return (UNDERSTOOD_THE_ASSIGNMENT);
	}
	init_bjsh(&bjsh);
	bjsh_loop(&bjsh);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

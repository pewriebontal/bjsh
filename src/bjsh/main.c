/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:06:55 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/20 22:40:12 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_bjsh(t_bjsh *bjsh)
{
	bjsh->status = CHILLING;
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

int	main(int argc, char *argv[])
{
	t_bjsh	bjsh;

	init_bjsh(&bjsh);
	bjsh_loop(&bjsh);
	return (UNDERSTOOD_THE_ASSIGNMENT);
}

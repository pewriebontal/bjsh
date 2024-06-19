/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:06 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 02:25:26 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_cd(char *path)
{
	if (path == NULL || *path == '\0')
	{
		path = getenv("HOME");
	}
	if (chdir(path) == -1)
	{
		display_error_msg("cd: no such file or directory: ");
		ft_printf("%s\n", path);
		return (1);
	}
	return (0);
}

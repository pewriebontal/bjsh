/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:02:44 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/21 00:42:55 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		yeet(buf);
		return (0);
	}
	else
	{
		perror("getcwd");
		return (1);
	}
}

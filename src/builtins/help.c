/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:58:39 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 17:31:26 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_help(void)
{
	ft_printf("%s (%s) [%s \"%s\" %s]\n", SHELL_SHORT_NAME, SHELL_LONG_NAME,
		SHELL_VERSION, GIT_COMMIT, SHELL_BUILD_DATE);
	ft_printf("💀 No help available!🫣🤭\n");
	ft_printf("😗 Go cry about it! 🤓🙊\n");
	return (0);
}

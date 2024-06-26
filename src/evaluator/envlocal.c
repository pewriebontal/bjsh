/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlocal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:06:21 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 01:21:51 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_local(char **envp, const char *key)
{
	int			i;
	const char	*equal_sign;
	char		*value;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
			return (NULL);
		if (ft_strncmp(envp[i], key, equal_sign - envp[i]) == 0)
		{
			value = ft_strdup(equal_sign + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

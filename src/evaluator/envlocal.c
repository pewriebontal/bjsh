/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlocal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:06:21 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 00:36:30 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path_env(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_strdup(path_env));
}

char	*get_env_local(char **envp, const char *key)
{
	int		i;
	char	*equal_sign;
	char	*value;

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

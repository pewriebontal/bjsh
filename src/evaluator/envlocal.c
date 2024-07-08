/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlocal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:06:21 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/08 21:30:05 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_local(char **envp, const char *key)
{
	int			i;
	const char	*equal_sign;
	char		*value;
	size_t		key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
			return (NULL);
		if (((size_t)(equal_sign - envp[i]) == key_len) && (ft_strncmp(envp[i],
					key, key_len) == 0))
		{
			value = ft_strdup(equal_sign + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*get_env_local2(t_env *env, const char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:54:31 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 20:56:22 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**allocate_envp(int count)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (envp);
}

char	*create_env_string(const char *key, const char *value)
{
	int		length;
	char	*env_string;

	length = ft_strlen(key) + ft_strlen(value) + 2;
	env_string = (char *)malloc(length);
	if (!env_string)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	snprintf(env_string, length, "%s=%s", key, value);
	return (env_string);
}

char	**convert_env_to_envp(t_env *env)
{
	int		count;
	t_env	*current;
	char	**envp;
	int		i;

	count = count_env_vars(env);
	envp = allocate_envp(count);
	current = env;
	i = 0;
	while (i < count)
	{
		envp[i] = create_env_string(current->key, current->value);
		current = current->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

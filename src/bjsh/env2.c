/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:15:45 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 20:55:34 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to create a new environment node
t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

// Function to split the key and value from an environment string
void	split_env(const char *env_str, char **key, char **value)
{
	const char	*equal_sign = ft_strchr(env_str, '=');

	if (!equal_sign)
	{
		*key = ft_strdup(env_str);
		*value = NULL;
	}
	else
	{
		*key = ft_strndup(env_str, equal_sign - env_str);
		*value = ft_strdup(equal_sign + 1);
	}
}

// Function to initialize the head and tail of the environment list
void	initialize_env_list(t_env **head, t_env **tail)
{
	*head = NULL;
	*tail = NULL;
}

// Helper function to remove an environment variable
void	remove_env(t_env **env, const char *key)
{
	t_env	*current;

	if (!key)
		return ;
	current = find_env(*env, key);
	if (current)
	{
		if (current->prev)
			current->prev->next = current->next;
		else
			*env = current->next;
		if (current->next)
			current->next->prev = current->prev;
		free(current->key);
		free(current->value);
		free(current);
	}
}

int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:06:36 by klinn             #+#    #+#             */
/*   Updated: 2024/06/22 21:22:04 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_env(t_bjsh *bjsh)
{
	t_env	*env;

	env = bjsh->env;
	while (env)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}

// Helper function to find an environment variable by key
t_env	*find_env(t_env *env, const char *key)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

// Helper function to add or update an environment variable
void	add_or_update_env(t_env **env, const char *key, const char *value)
{
	t_env	*existing_node;
	t_env	*new_node;

	if (!key || !value)
		return ;
	existing_node = find_env(*env, key);
	if (existing_node)
	{
		free(existing_node->value);
		existing_node->value = ft_strdup(value);
		if (!existing_node->value)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_node = create_env_node(key, value);
		new_node->next = *env;
		if (*env)
			(*env)->prev = new_node;
		*env = new_node;
	}
}

void debug_env(char **envp)
{
	int i = 0;
	ft_printf("Debugging envp\n");
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
}
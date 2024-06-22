/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:25:29 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 19:59:59 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to find an environment node by key
t_env	*find_env_node(t_env *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

// Function to export an environment variable (add or update)
int	bjsh_export(t_bjsh *bjsh, const char *key, const char *value)
{
	t_env	*node;
	t_env	*new_node;

	if (!bjsh || !key)
		return (-1);
	node = find_env_node(bjsh->env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1);
	}
	else
	{
		new_node = create_env_node(key, value);
		if (!new_node)
			return (-1);
		append_env_node(&(bjsh->env), new_node);
	}
	return (0);
}

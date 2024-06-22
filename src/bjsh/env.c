/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:04:35 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 19:15:57 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to append a new node to the end of the environment list
void	append_env_node(t_env **tail, t_env *new_node)
{
	if (!*tail)
	{
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
}

// Function to create the environment list from envp
void	create_env_list(t_bjsh *bjsh, t_env **head, t_env **tail)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_node;

	i = 0;
	while (bjsh->envp[i])
	{
		key = NULL;
		value = NULL;
		split_env(bjsh->envp[i], &key, &value);
		new_node = create_env_node(key, value);
		free(key);
		free(value);
		if (!new_node)
			return ;
		if (!*head)
		{
			*head = new_node;
			*tail = new_node;
		}
		else
			append_env_node(tail, new_node);
		i++;
	}
}

// Function to initialize the bjsh environment linked list
void	bjsh_env_init(t_bjsh *bjsh)
{
	t_env	*head;
	t_env	*tail;

	if (!bjsh || !bjsh->envp)
		return ;
	initialize_env_list(&head, &tail);
	create_env_list(bjsh, &head, &tail);
	bjsh->env = head;
}

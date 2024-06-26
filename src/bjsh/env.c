/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:04:35 by klinn             #+#    #+#             */
/*   Updated: 2024/06/27 01:25:23 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to append a new node to the end of the environment list
void	append_env_node(t_env **head, t_env *new_node)
{
	t_env	*tail;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_node;
	new_node->prev = tail;
	new_node->next = NULL;
}

t_env	*create_env_list(const t_bjsh *bjsh)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (bjsh->envp[i])
	{
		process_env_variable(bjsh->envp[i], &head);
		i++;
	}
	return (head);
}

// Function to initialize the bjsh environment linked list
void	bjsh_env_init(t_bjsh *bjsh)
{
	t_env	*head;

	if (!bjsh || !bjsh->envp)
		return ;
	head = create_env_list(bjsh);
	bjsh->env = head;
}

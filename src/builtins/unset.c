/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:25:40 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 20:46:20 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Function to unset an environment variable (remove)
int	bjsh_unset(t_bjsh *bjsh, const char *key)
{
	t_env	*node;

	if (!bjsh || !key)
		return (-1);
	node = find_env_node(bjsh->env, key);
	if (!node)
		return (0);
	if (node->prev)
		node->prev->next = node->next;
	else
		bjsh->env = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
	return (0);
}

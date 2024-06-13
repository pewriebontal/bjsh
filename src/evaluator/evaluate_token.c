/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:22:49 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/14 02:19:12 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	evaluate_token_chain(t_token *token)
{
	remove_empty_nodes(token);
	evaluate_token_type(token);
	fill_up_token_with_env(token);
	// evaluate_token_chain(token);
}

// this function will remove empty nodes from the token chain
// for example, if the token chain is like this:
// "ls" -> "" -> "echo"
// then the chain will be modified to:
// "ls" -> "echo"

void	remove_empty_nodes(t_token *token)
{
	t_token *tmp;
	t_token *next;

	tmp = token;
	while (tmp)
	{
		if (ft_strlen(tmp->str) == 0)
		{
			next = tmp->next;
			if (tmp->prev)
				tmp->prev->next = next;
			if (next)
				next->prev = tmp->prev;
			free(tmp->str);
			free(tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}
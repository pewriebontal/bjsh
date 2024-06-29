/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:22:49 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 16:41:53 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	evaluate_token_chain(t_token *token, t_bjsh *bjsh)
{
	remove_empty_nodes(token);
	evaluate_token_type(token);
	fill_up_token_with_env(token, bjsh);
}

void	remove_empty_nodes(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

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
			yeet(tmp->str);
			yeet(tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}

int	check_invalid_pipe_sequence(t_token *head)
{
	t_token	*current;

	if (head == NULL)
		return (0);
	current = head;
	if (current->type == PIPE)
	{
		ft_dprintf(STDERR_FILENO,
			"🤌 ❯ syntax error near unexpected token `|'\n");
		return (1);
	}
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL || current->next->type == PIPE)
			{
				ft_dprintf(STDERR_FILENO,
					"🤌 ❯ syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

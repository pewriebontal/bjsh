/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:44:22 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 22:57:29 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <byamc/byamc.h>
#include <minishell.h>

t_token	*array_to_list(char **arr)
{
	t_token	*head;
	t_token	*token;
	t_token	*prev;
	int		i;

	i = 0;
	head = NULL;
	prev = NULL;
	while (arr[i])
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->str = arr[i];
		token->type = 0;
		token->executed = 0;
		token->prev = prev;
		token->next = NULL;
		if (prev)
			prev->next = token;
		if (!head)
			head = token;
		prev = token;
		i++;
	}
	return (head);
}

void	debug_print_list(t_token *token)
{
	while (token)
	{
		ft_printf("token: %s\t\t", token->str);
		ft_printf("type: %d\n", token->type);
		token = token->next;
	}
}

void	clear_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->str);
		free(token);
		token = next;
	}
}

void	clear_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

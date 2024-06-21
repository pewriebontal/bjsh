/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:45:07 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 04:08:08 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_and_insert_tokens(t_token *token, char *str, size_t prefix_len,
		char *redirection)
{
	t_token	*redirection_token;
	t_token	*suffix_token;
	char	*prefix;

	redirection_token = create_token(redirection, token->type);
	create_suffix_token(str, prefix_len, redirection, &suffix_token);
	if (prefix_len > 0)
	{
		prefix = ft_strndup(str, prefix_len);
		free(token->str);
		token->str = prefix;
	}
	else
	{
		token->str = ft_strdup(redirection);
		free(redirection_token->str);
		redirection_token = token;
	}
	if (redirection_token != token)
	{
		insert_after(token, redirection_token);
	}
	insert_after(redirection_token, suffix_token);
}

void	process_redirection(t_token *token, char *str, size_t i)
{
	size_t	prefix_len;
	char	redirection[3];

	redirection[0] = '\0';
	redirection[1] = '\0';
	redirection[2] = '\0';
	prefix_len = i;
	set_redirection(str, i, redirection);
	create_and_insert_tokens(token, str, prefix_len, redirection);
}

void	split_token(t_token *token)
{
	char	*str;
	size_t	len;
	int		in_single_quote;
	int		in_double_quote;
	size_t	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	if (!token || !token->str)
		return ;
	str = token->str;
	len = ft_strlen(str);
	while (i < len)
	{
		handle_quotes_split_internal(str[i], &in_single_quote,
			&in_double_quote);
		if (!in_single_quote && !in_double_quote && is_redirection(str[i], str[i
					+ 1]))
		{
			process_redirection(token, str, i);
			return ;
		}
		i++;
	}
}

void	split_token_chain_redirect(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current)
	{
		next = current->next;
		split_token(current);
		current = next;
	}
}

void	insert_after(t_token *current, t_token *new_token)
{
	if (!current || !new_token)
		return ;
	new_token->next = current->next;
	new_token->prev = current;
	if (current->next)
	{
		current->next->prev = new_token;
	}
	current->next = new_token;
}

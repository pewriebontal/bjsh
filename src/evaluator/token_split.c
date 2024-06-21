/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:45:07 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 01:22:20 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create_token(char *str, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	new_token->type = type;
	new_token->executed = 0;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	insert_after(t_token *current, t_token *new_token)
{
	if (!current || !new_token)
		return ;
	new_token->next = current->next;
	new_token->prev = current;
	if (current->next)
		current->next->prev = new_token;
	current->next = new_token;
}

void	split_token(t_token *token)
{
	char	*str;
	size_t	len;
	int		in_single_quote;
	int		in_double_quote;
	size_t	prefix_len;
	size_t	suffix_len;
	char	redirection[3] = {0};
	t_token	*redirection_token;
	char	*suffix;
	t_token	*suffix_token;
	char	*prefix;

	in_single_quote = 0;
	in_double_quote = 0;
	if (!token || !token->str)
		return ;
	str = token->str;
	len = ft_strlen(str);
	in_single_quote = 0, in_double_quote = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		else if (!in_single_quote && !in_double_quote)
		{
			if ((i < len - 1 && (str[i] == '>' && str[i + 1] == '>'))
				|| (i < len - 1 && (str[i] == '<' && str[i + 1] == '<'))
				|| str[i] == '>' || str[i] == '<')
			{
				// Calculate the lengths of the two parts
				prefix_len = i;
				suffix_len = len - prefix_len - ((str[i + 1] == '>' || str[i
							+ 1] == '<') ? 2 : 1);
				// Create the redirection token
				if (str[i + 1] == '>' || str[i + 1] == '<')
				{
					redirection[0] = str[i];
					redirection[1] = str[i + 1];
				}
				else
				{
					redirection[0] = str[i];
				}
				redirection_token = create_token(redirection, token->type);
				// Create the suffix token
				suffix = str + i + ((str[i + 1] == '>' || str[i
							+ 1] == '<') ? 2 : 1);
				suffix_token = create_token(suffix, token->type);
				// Update the current token to the prefix
				if (prefix_len > 0)
				{
					prefix = ft_strndup(str, prefix_len);
					free(token->str);
					token->str = prefix;
				}
				else
				{
					// If there's no prefix,
					//	move redirection token to the current position
					token->str = ft_strdup(redirection);
					free(redirection_token->str);
					redirection_token = token;
				}
				// Insert the new tokens into the linked list
				if (redirection_token != token)
					insert_after(token, redirection_token);
				insert_after(redirection_token, suffix_token);
				return ;
				// Exit the function after handling the first redirection
			}
		}
	}
}

void	split_token_chain_redirect(t_token *token)
{
	t_token *current = token;
	while (current)
	{
		t_token *next = current->next;
		split_token(current);
		current = next;
	}
}
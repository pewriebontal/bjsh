/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 03:47:31 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 04:08:11 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create_token(const char *str, int type)
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

void	handle_quotes_split_internal(char c, int *in_single_quote,
		int *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
	}
	else if (c == '\"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
	}
}

int	is_redirection(char c, char next)
{
	return ((c == '>' && next == '>') || (c == '<' && next == '<') || c == '>'
		|| c == '<');
}

void	set_redirection(char *str, size_t i, char *redirection)
{
	if (str[i + 1] == '>' || str[i + 1] == '<')
	{
		redirection[0] = str[i];
		redirection[1] = str[i + 1];
	}
	else
	{
		redirection[0] = str[i];
	}
}

void	create_suffix_token(char *str, size_t prefix_len, char *redirection,
		t_token **suffix_token)
{
	char	*suffix;

	if (redirection[1] != '\0')
	{
		suffix = str + prefix_len + 2;
	}
	else
	{
		suffix = str + prefix_len + 1;
	}
	*suffix_token = create_token(suffix, 0);
}

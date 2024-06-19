/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:38:11 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 01:48:07 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_special_characters(char *str, char special_character)
{
	while (*str != '\0')
	{
		if (*str == special_character)
		{
			*str = ' ';
		}
		str++;
	}
}

void	replace_special_characters_in_node(t_token *token,
		char special_character)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		replace_special_characters(current->str, special_character);
		current = current->next;
	}
}

t_token	*create_token_node(const char *str, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->str = ft_strdup(str);
	new->type = type;
	new->executed = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	is_within_quotes(const char *str, const char *pos)
{
	int			in_single_quote;
	int			in_double_quote;
	const char	*p;

	in_single_quote = 0;
	in_double_quote = 0;
	p = str;
	while (p < pos)
	{
		if (*p == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*p == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		p++;
	}
	return (in_single_quote || in_double_quote);
}

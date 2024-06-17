/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:02:10 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 22:45:02 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*bon_and_jason_tokenizer(char *command_input)
{
	t_token	*token;
	char	**args;

	replace_spaces_in_quotes(command_input);
	args = ft_split(command_input, ' ');
	token = array_to_list(args);
	token = token_split_redirect(token);
	evaluate_token_chain(token);
	replace_special_characters_in_node(token);
	token = remove_quotes_from_token(token);
	free(command_input);
	return (token);
}

t_token	*remove_quotes_from_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->str != NULL)
		{
			remove_quotes(current->str);
		}
		current = current->next;
	}
	return (token);
}

void	remove_quotes(char *str)
{
	char	*dst;
	char	*src;
	int		in_single_quote;
	int		in_double_quote;

	dst = str;
	src = str;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*src)
	{
		if (*src == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*src == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

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

void	replace_special_characters_in_node(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		replace_special_characters(current->str, '^');
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
	int in_single_quote = 0;
	int in_double_quote = 0;

	for (const char *p = str; p < pos; p++)
	{
		if (*p == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*p == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
	}
	return (in_single_quote || in_double_quote);
}
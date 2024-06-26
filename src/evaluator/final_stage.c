/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_stage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:02:19 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 16:58:33 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_add_back(t_token **new_token, t_token *new_node)
{
	t_token	*temp;

	if (*new_token == NULL)
	{
		*new_token = new_node;
	}
	else
	{
		temp = *new_token;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

// Helper function to create a new token
t_token	*create_new_token(char *str, int type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(str);
	new_node->type = type;
	new_node->executed = 0;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

// Function to split the token string by special characters
void	split_by_special_chars(char *str, t_token **new_token)
{
	char	*special_chars[] = {">>", ">", "<<", "<", "|", NULL};
	int		special_types[] = {REDIRECT_OUT_APPEND, REDIRECT_OUT,
				REDIRECT_IN_HERE, REDIRECT_IN, PIPE};
	char	*substr;
	int		special_len;

	int i, j, type, in_single_quote, in_double_quote, len;
	len = ft_strlen(str);
	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
		{
			j = 0;
			while (special_chars[j])
			{
				special_len = ft_strlen(special_chars[j]);
				if (ft_strncmp(&str[i], special_chars[j], special_len) == 0)
				{
					if (i > 0)
					{
						substr = ft_strndup(str, i);
						token_add_back(new_token, create_new_token(substr, -1));
						free(substr);
					}
					type = special_types[j];
					substr = ft_strndup(&str[i], special_len);
					token_add_back(new_token, create_new_token(substr, type));
					free(substr);
					str += i + special_len;
					len -= i + special_len;
					i = -1;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	if (*str)
		token_add_back(new_token, create_new_token(str, -1));
}

// this function walk through the token chain
// and split by special characters and add back
// to the new token chain
// for example: ls -la|wc -> would be come ls -la | wc
// and return the new token chain
// another example: ls -la >> >file -> would be come ls -la >> > file
// another example: ls -la >> >>file|wc -> would be come ls -la >> >> file | wc

// so it need to check current node's string and scan from the beginning
// to end of the string and check if there is any special characters
// if there is any special characters,
//	it will split the first part of the string
// and create a new token and add back to the new token chain and it's type

// rules:
// >> comes first than >
// dont split if string is in single quote or double quote

// Main function to walk through the token chain and split by special characters
t_token	*final_stage(t_token *token)
{
	t_token	*new_token;
	t_token	*current;

	new_token = NULL;
	current = token;
	while (current)
	{
		split_by_special_chars(current->str, &new_token);
		current = current->next;
	}
	clear_list(token);
	return (new_token);
}

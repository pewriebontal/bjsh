/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_stage2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:32 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 17:23:32 by mkhaing          ###   ########.fr       */
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

void	handle_quotes2(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

void	add_token(char *str, int length, t_token **new_token, int type)
{
	char	*substr;

	substr = ft_strndup(str, length);
	token_add_back(new_token, create_new_token(substr, type));
	free(substr);
}

int	get_special_char_length(char *str, char **special_chars)
{
	int	j;
	int	special_len;

	j = 0;
	while (special_chars[j])
	{
		special_len = ft_strlen(special_chars[j]);
		if (ft_strncmp(str, special_chars[j], special_len) == 0)
		{
			return (special_len);
		}
		j++;
	}
	return (0);
}

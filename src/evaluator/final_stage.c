/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_stage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:02:19 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 17:24:45 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_special_char_type(char *str, char **special_chars, int *special_types)
{
	int	j;
	int	special_len;

	j = 0;
	while (special_chars[j])
	{
		special_len = ft_strlen(special_chars[j]);
		if (ft_strncmp(str, special_chars[j], special_len) == 0)
		{
			return (special_types[j]);
		}
		j++;
	}
	return (-1);
}

int	check_special_chars(char *str, t_token **new_token, int i)
{
	char	*special_chars[6];
	int		special_types[5];
	int		special_len;
	int		type;

	init_special_chars(special_chars, special_types);
	special_len = get_special_char_length(&str[i], special_chars);
	if (special_len > 0)
	{
		if (i > 0)
		{
			add_token(str, i, new_token, -1);
		}
		type = find_special_char_type(&str[i], special_chars, special_types);
		add_token(&str[i], special_len, new_token, type);
		return (special_len);
	}
	return (0);
}

void	split_by_special_chars(char *str, t_token **new_token)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;
	int	len;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		handle_quotes2(str[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
		{
			i = process_special_chars(&str, &len, i, new_token);
		}
		i++;
	}
	if (*str)
	{
		add_substring_token(str, ft_strlen(str), new_token, -1);
	}
}

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

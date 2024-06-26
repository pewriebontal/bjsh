/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:38:11 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 00:59:19 by mkhaing          ###   ########.fr       */
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

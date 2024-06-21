/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 03:33:28 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_spaces_in_quotes(char *str)
{
	int		inside_single_quotes;
	int		inside_double_quotes;
	char	*ptr;

	inside_single_quotes = 0;
	inside_double_quotes = 0;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '\'' && !inside_double_quotes)
		{
			inside_single_quotes = !inside_single_quotes;
		}
		else if (*ptr == '"' && !inside_single_quotes)
		{
			inside_double_quotes = !inside_double_quotes;
		}
		else if ((inside_single_quotes || inside_double_quotes) && *ptr == ' ')
		{
			*ptr = '`';
		}
		ptr++;
	}
}

int	count_weired_character(char *str)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '`')
		{
			count++;
		}
		ptr++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/19 22:30:29 by mkhaing          ###   ########.fr       */
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

void	replace_spaces_in_quotes1(char *str)
{
	int		inside_single_quotes;
	int		inside_double_quotes;
	int		single_quote_count;
	int		double_quote_count;
	char	*ptr;

	inside_single_quotes = 0;
	inside_double_quotes = 0;
	single_quote_count = 0;
	double_quote_count = 0;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '\'')
			single_quote_count++;
		else if (*ptr == '"')
			double_quote_count++;
		ptr++;
	}
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
		return ;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (*ptr == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else if ((inside_single_quotes || inside_double_quotes) && *ptr == ' ')
			*ptr = '`';
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

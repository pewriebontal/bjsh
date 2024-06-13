/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:43 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/14 01:04:51 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// this function will check if string have quotes
// if it does, it will check any spaces inside the quotes
// and replace them with a special character
// so that we can split the string by spaces later
// without splitting the words inside the quotes
// for example, if the string is like this:

// "hello world" "this is a test"
// then the string will be modified to:
// "helloЙworld" "thisЙisЙaЙtest"

// this function will return the modified string

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
			*ptr = '^'; // Replace space with a special character
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
	// First pass to count quotes
	while (*ptr != '\0')
	{
		if (*ptr == '\'')
		{
			single_quote_count++;
		}
		else if (*ptr == '"')
		{
			double_quote_count++;
		}
		ptr++;
	}
	// Check if quotes are balanced
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
	{
		// Unbalanced quotes, do not replace spaces
		return ;
	}
	// Reset pointer for second pass
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
			*ptr = '^';
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
		if (*ptr == '^')
		{
			count++;
		}
		ptr++;
	}
	return (count);
}

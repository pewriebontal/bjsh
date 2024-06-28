/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:23:49 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 03:23:04 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_char_to_result(char c, char **result, size_t *result_len)
{
	*result = ft_realloc(*result, *result_len + 2);
	(*result)[(*result_len)++] = c;
	(*result)[*result_len] = '\0';
}

void	append_string_to_result(const char *str, char **result,
		size_t *result_len)
{
	size_t	len;

	len = ft_strlen(str);
	*result = ft_realloc(*result, *result_len + len + 1);
	ft_strcpy(*result + *result_len, str);
	*result_len += len;
	(*result)[*result_len] = '\0';
}

void	replace_env_vars(char **str, t_bjsh *bjsh)
{
	t_env_replacer	replacer;
	char			*p;

	replacer.result = NULL;
	replacer.in_single_quote = 0;
	replacer.in_double_quote = 0;
	replacer.result_len = 0;
	p = *str;
	while (*p)
	{
		p = handle_quotes(p, &replacer);
		if (*p == '$' && !replacer.in_single_quote)
			p = handle_dollar_sign(p, &replacer, bjsh);
		else
		{
			append_char_to_result(*p, &replacer.result, &replacer.result_len);
			p++;
		}
	}
	if (replacer.result)
	{
		free(*str);
		*str = replacer.result;
	}
}

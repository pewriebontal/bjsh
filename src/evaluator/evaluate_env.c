/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:56:04 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 18:56:12 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fill_up_token_with_env(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		replace_env_vars(&current->str);
		current = current->next;
	}
}

void	replace_env_vars(char **str)
{
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
	char	*p;
	size_t	result_len;
	size_t	before_len;
	size_t	after_len;

	result = NULL;
	char *env_start, *env_end, *env_name, *env_value;
	in_single_quote = 0;
	in_double_quote = 0;
	p = *str;
	while (*p)
	{
		if (*p == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			p++;
			continue ;
		}
		else if (*p == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			p++;
			continue ;
		}
		else if (*p == '$' && !in_single_quote)
		{
			env_start = p + 1;
			env_end = env_start;
			while (*env_end && (*env_end == '_' || isalnum(*env_end)))
			{
				env_end++;
			}
			env_name = strndup(env_start, env_end - env_start);
			env_value = getenv(env_name);
			free(env_name);
			if (env_value)
			{
				result_len = result ? ft_strlen(result) : 0;
				before_len = p - *str;
				after_len = ft_strlen(env_end);
				result = realloc(result, result_len + before_len
						+ ft_strlen(env_value) + after_len + 1);
				if (result_len == 0)
				{
					strncpy(result, *str, before_len);
				}
				ft_strcpy(result + result_len + before_len, env_value);
				ft_strcpy(result + result_len + before_len
					+ ft_strlen(env_value), env_end);
				p = result + result_len + before_len + ft_strlen(env_value);
			}
			else
			{
				p = env_end;
			}
			continue ;
		}
		p++;
	}
	if (result)
	{
		free(*str);
		*str = result;
	}
}
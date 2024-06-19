/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:56:04 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/19 16:40:45 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void fill_up_token_with_env(t_token *token, t_bjsh *bjsh)
{
	t_token *current;

	current = token;
	while (current != NULL)
	{
		replace_env_vars(&current->str, bjsh);
		current = current->next;
	}
}

// replace with env variabel
char	*expand_env(char *arr)
{
	int		len;
	char	*env_arr;

	env_arr = (char *)malloc(sizeof(char *) * 1024);
	if (*arr == '$')
	{
		*arr++;
		ft_strlcpy(env_arr, arr, sizeof(env_arr));
		return (getenv(env_arr));
	}
	return (arr);
}

void replace_env_vars(char **str, t_bjsh *bjsh)
{
	char *result;
	int in_single_quote;
	int in_double_quote;
	char *p;
	size_t result_len;
	size_t before_len;
	size_t after_len;

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
			continue;
		}
		else if (*p == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			p++;
			continue;
		}
		else if (*p == '$' && !in_single_quote)
		{
			if (*(p + 1) == '?')
			{
				env_value = ft_itoa(bjsh->last_exit_status);
				result_len = result ? ft_strlen(result) : 0;
				before_len = p - *str;
				after_len = ft_strlen(p + 2); // Skip $? characters
				result = realloc(result, result_len + before_len + ft_strlen(env_value) + after_len + 1);
				if (result_len == 0)
				{
					strncpy(result, *str, before_len);
				}
				ft_strcpy(result + result_len + before_len, env_value);
				ft_strcpy(result + result_len + before_len + ft_strlen(env_value), p + 2);
				p = result + result_len + before_len + ft_strlen(env_value);
				free(env_value);
				continue;
			}
			else
			{
				env_start = p + 1;
				env_end = env_start;
				while (*env_end && (*env_end == '_' || ft_isalnum(*env_end)))
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
					result = realloc(result, result_len + before_len + ft_strlen(env_value) + after_len + 1);
					if (result_len == 0)
					{
						strncpy(result, *str, before_len);
					}
					ft_strcpy(result + result_len + before_len, env_value);
					ft_strcpy(result + result_len + before_len + ft_strlen(env_value), env_end);
					p = result + result_len + before_len + ft_strlen(env_value);
				}
				else
				{
					p = env_end;
				}
				continue;
			}
		}
		p++;
	}
	if (result)
	{
		free(*str);
		*str = result;
	}
}

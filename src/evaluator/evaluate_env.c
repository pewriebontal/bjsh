/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:56:04 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/22 02:53:52 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fill_up_token_with_env(t_token *token, t_bjsh *bjsh)
{
	t_token	*current;

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

void	replace_env_vars(char **str, t_bjsh *bjsh)
{
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
	char	*p;
	size_t	result_len;
	char	*env_value;
	char	*env_start;
	char	*env_end;
	char	*env_name;
	size_t	env_value_len;

	result = NULL;
	in_single_quote = 0;
	in_double_quote = 0;
	p = *str;
	result_len = 0;
	while (*p)
	{
		if (*p == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			result = realloc(result, result_len + 2);
			result[result_len++] = *p++;
			result[result_len] = '\0';
			continue ;
		}
		else if (*p == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			result = realloc(result, result_len + 2);
			result[result_len++] = *p++;
			result[result_len] = '\0';
			continue ;
		}
		else if (*p == '$' && !in_single_quote)
		{
			env_start = p + 1;
			env_end = env_start;
			if (*env_start == '?')
			{
				env_value = ft_itoa(bjsh->last_exit_status);
				env_end++;
			}
			else
			{
				while (*env_end && (*env_end == '_' || isalnum(*env_end)))
				{
					env_end++;
				}
				env_name = ft_strndup(env_start, env_end - env_start);
				env_value = getenv(env_name);
				free(env_name);
				if (!env_value)
				{
					env_value = "";
				}
			}
			env_value_len = ft_strlen(env_value);
			result = realloc(result, result_len + env_value_len + 1);
			ft_strcpy(result + result_len, env_value);
			result_len += env_value_len;
			result[result_len] = '\0';
			p = env_end;
			if (*env_start == '?')
			{
				free(env_value);
			}
			continue ;
		}
		else
		{
			result = realloc(result, result_len + 2);
			result[result_len++] = *p++;
			result[result_len] = '\0';
		}
	}
	if (result)
	{
		free(*str);
		*str = result;
	}
}

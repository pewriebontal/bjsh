/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:29:26 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 03:13:03 by mkhaing          ###   ########.fr       */
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

char	*handle_quotes(char *p, t_env_replacer *replacer)
{
	if (*p == '\'' && !replacer->in_double_quote)
	{
		replacer->in_single_quote = !replacer->in_single_quote;
		append_char_to_result(*p, &replacer->result, &replacer->result_len);
		p++;
	}
	else if (*p == '\"' && !replacer->in_single_quote)
	{
		replacer->in_double_quote = !replacer->in_double_quote;
		append_char_to_result(*p, &replacer->result, &replacer->result_len);
		p++;
	}
	return (p);
}

char	*handle_dollar_sign(char *p, t_env_replacer *replacer, t_bjsh *bjsh)
{
	char	*env_start;
	char	*env_end;
	char	*env_value;
	char	*env_name;

	if (replacer->in_single_quote)
	{
		append_char_to_result(*p, &replacer->result, &replacer->result_len);
		return (p + 1);
	}
	env_start = p + 1;
	env_end = env_start;
	if (*env_start == '?')
	{
		env_value = ft_itoa(bjsh->last_exit_status);
		env_end++;
	}
	else
	{
		while (*env_end && (*env_end == '_' || ft_isalnum(*env_end)))
			env_end++;
		if (env_start == env_end)
		{
			append_char_to_result(*p, &replacer->result, &replacer->result_len);
			return (p + 1);
		}
		env_name = ft_strndup(env_start, env_end - env_start);
		env_value = get_env_local(bjsh->envp, env_name);
		free(env_name);
		if (!env_value)
			env_value = "";
	}
	append_string_to_result(env_value, &replacer->result,
		&replacer->result_len);
	p = env_end;
	if (*env_start == '?')
		free(env_value);
	return (p);
}

void	append_char_to_result(char c, char **result, size_t *result_len)
{
	*result = realloc(*result, *result_len + 2);
	(*result)[(*result_len)++] = c;
	(*result)[*result_len] = '\0';
}

void	append_string_to_result(char *str, char **result, size_t *result_len)
{
	size_t	len;

	len = ft_strlen(str);
	*result = realloc(*result, *result_len + len + 1);
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

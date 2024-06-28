/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:29:26 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 20:25:00 by mkhaing          ###   ########.fr       */
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
	else if (env_value != NULL && env_value[0] != '\0')
		free(env_value);
	return (p);
}

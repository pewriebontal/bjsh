/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:29:26 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/13 17:38:21 by mkhaing          ###   ########.fr       */
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

char	*pid_return(char **env_end)
{
	char	*env_value;

	env_value = ft_itoa(getpid());
	(*env_end)++;
	return (env_value);
}

char	*question_mark_return(t_bjsh *bjsh, char **env_end)
{
	char	*env_value;

	env_value = ft_itoa(bjsh->last_exit_status);
	(*env_end)++;
	return (env_value);
}

char	*handle_dollar_sign(char *p, t_env_replacer *replacer, t_bjsh *bjsh)
{
	char	*env_start;
	char	*env_end;
	char	*env_value;

	if (replacer->in_single_quote)
		return (suka(p, replacer));
	env_start = p + 1;
	env_end = env_start;
	if (*env_start == '?')
		env_value = question_mark_return(bjsh, &env_end);
	else if (*env_start == '$')
		env_value = pid_return(&env_end);
	else
	{
		env_value = handle_env_var_a(env_start, &env_end, bjsh);
		if (env_start == env_end)
			return (suka(p, replacer));
	}
	append_string_to_result(env_value, &replacer->result,
		&replacer->result_len);
	p = env_end;
	if ((*env_start == '?') || (env_value != NULL && env_value[0] != '\0'))
		yeet(env_value);
	return (p);
}

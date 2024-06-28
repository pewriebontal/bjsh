/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:23:27 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 05:18:49 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*suka(char *p, t_env_replacer *replacer)
{
	append_char_to_result(*p, &replacer->result, &replacer->result_len);
	return (p + 1);
}

char	*handle_env_var_a(char *env_start, char **env_end, t_bjsh *bjsh)
{
	char	*env_name;
	char	*env_value;

	while (**env_end && (**env_end == '_' || ft_isalnum(**env_end)))
		(*env_end)++;
	env_name = ft_strndup(env_start, *env_end - env_start);
	env_value = get_env_local(bjsh->envp, env_name);
	free(env_name);
	if (!env_value)
		env_value = "";
	return (env_value);
}

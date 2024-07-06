/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:06:36 by klinn             #+#    #+#             */
/*   Updated: 2024/07/06 23:57:39 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bjsh_env(t_bjsh *bjsh)
{
	t_env	*env;

	env = bjsh->env;
	while (env)
	{
		ft_dprintf(STDOUT_FILENO, "%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	bjsh_env2(t_bjsh *bjsh)
{
	t_env	*env;

	env = bjsh->env;
	while (env)
	{
		if (env->value)
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			ft_printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
}

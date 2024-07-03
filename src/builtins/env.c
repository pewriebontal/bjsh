/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 02:06:36 by klinn             #+#    #+#             */
/*   Updated: 2024/07/03 08:45:52 by mkhaing          ###   ########.fr       */
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

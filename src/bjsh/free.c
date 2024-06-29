/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:36:27 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 18:39:25 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	looper_yeet(t_bjsh *bjsh, t_token *token)
{
	if (bjsh->token)
	{
		if (bjsh->token != token)
		{
			yeet_token(bjsh->token);
		}
		bjsh->token = NULL;
	}
	if (token && bjsh->token != token)
	{
		yeet_token(token);
	}
	if (!bjsh->first_run && bjsh->envp)
		ft_free_multidi((void **)bjsh->envp, 2);
}

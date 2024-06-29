/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:36:27 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/29 17:46:02 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	looper_yeet(t_bjsh *bjsh, t_token *token)
{
	if (bjsh->token)
		yeet_token(bjsh->token);
	else if (token)
		yeet_token(token);
	if (!bjsh->first_run)
		ft_free_multidi((void **)bjsh->envp, 2);
}

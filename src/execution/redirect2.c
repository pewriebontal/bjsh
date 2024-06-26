/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:28:54 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/27 02:09:31 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_invalid_redirect_sequence(t_exe_context *context)
{
	if (context->current->next == NULL)
	{
		ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n",
			context->current->str);
		return (-1);
	}
	else if (context->current->next->type == REDIRECT_OUT
		|| context->current->next->type == REDIRECT_OUT_APPEND
		|| context->current->next->type == REDIRECT_IN
		|| context->current->next->type == REDIRECT_IN_HERE)
	{
		ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `%s'\n",
			context->current->next->str);
		context->current = context->current->next;
		return (-1);
	}
	return (0);
}

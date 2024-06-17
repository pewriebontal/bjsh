/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:11:52 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 22:33:41 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	evaluate_token_type(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		update_token_type(tmp);
		tmp = tmp->next;
	}
}

void	update_token_type(t_token *token)
{
	if (!token || !token->str)
		return ;
	if (ft_strcmp(token->str, ">") == 0)
		token->type = REDIRECT_OUT;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = REDIRECT_OUT_APPEND;
	else if (ft_strcmp(token->str, "<<<") == 0)
		token->type = REDIRECT_HERE_STRING;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = REDIRECT_IN;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = REDIRECT_IN_HERE;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else
		token->type = -1;
}

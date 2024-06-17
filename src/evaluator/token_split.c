/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:45:07 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 22:45:56 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*split_token(t_token *token, char *pos, const char *redir,
		int redir_type)
{
	char	*before;
	char	*after;
	t_token	*before_token;
	t_token	*redirect_token;
	t_token	*after_token;

	if (pos != token->str)
	{
		before = strndup(token->str, pos - token->str);
		after = ft_strdup(pos + ft_strlen(redir));
		before_token = create_token_node(before, 0);
		redirect_token = create_token_node(redir, redir_type);
		after_token = create_token_node(after, 0);
		before_token->next = redirect_token;
		redirect_token->prev = before_token;
		redirect_token->next = after_token;
		after_token->prev = redirect_token;
		after_token->next = token->next;
		if (token->next)
			token->next->prev = after_token;
		if (token->prev)
			token->prev->next = before_token;
		else
			token = before_token;
		before_token->prev = token->prev;
		free(token->str);
		free(token);
		free(before);
		free(after);
		return (after_token);
	}
	else
	{
		redirect_token = create_token_node(redir, redir_type);
		after = ft_strdup(pos + ft_strlen(redir));
		free(token->str);
		token->str = after;
		redirect_token->next = token;
		redirect_token->prev = token->prev;
		if (token->prev)
			token->prev->next = redirect_token;
		token->prev = redirect_token;
		if (token == token)
			token = redirect_token;
		return (token->next);
	}
}

t_token	*token_split_redirect(t_token *token)
{
	t_token	*tmp;
	char	*pos;

	tmp = token;
	while (tmp)
	{
		if ((pos = ft_strstr(tmp->str, "<<<")) != NULL
			&& !is_within_quotes(tmp->str, pos))
		{
			tmp = split_token(tmp, pos, "<<<", REDIRECT_HERE_STRING);
		}
		else if ((pos = ft_strstr(tmp->str, "<<")) != NULL
			&& !is_within_quotes(tmp->str, pos))
		{
			tmp = split_token(tmp, pos, "<<", REDIRECT_IN_HERE);
		}
		else if ((pos = ft_strstr(tmp->str, ">>")) != NULL
			&& !is_within_quotes(tmp->str, pos))
		{
			tmp = split_token(tmp, pos, ">>", REDIRECT_OUT_APPEND);
		}
		else if ((pos = ft_strstr(tmp->str, ">")) != NULL
			&& !is_within_quotes(tmp->str, pos))
		{
			tmp = split_token(tmp, pos, ">", REDIRECT_OUT);
		}
		else if ((pos = ft_strstr(tmp->str, "<")) != NULL
			&& !is_within_quotes(tmp->str, pos))
		{
			tmp = split_token(tmp, pos, "<", REDIRECT_IN);
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return (token);
}

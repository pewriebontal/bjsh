/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:02:10 by mkhaing           #+#    #+#             */
/*   Updated: 2024/07/06 23:55:58 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*bon_and_jason_tokenizer(char *command_input, t_bjsh *bjsh)
{
	t_token	*token;
	char	**args;

	replace_spaces_in_quotes(command_input);
	args = ft_split(command_input, ' ');
	token = array_to_list(args);
	replace_export_with_env(token);
	evaluate_token_chain(token, bjsh);
	replace_special_characters_in_node(token, (char)SAUCE);
	token = final_stage(token);
	token = remove_quotes_from_token(token);
	if (command_input)
		yeet(command_input);
	ft_free_multidi((void **)args, 1);
	return (token);
}

t_token	*remove_quotes_from_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->str != NULL)
		{
			remove_quotes(current->str);
		}
		current = current->next;
	}
	return (token);
}

void	remove_quotes(char *str)
{
	char	*dst;
	char	*src;
	int		in_single_quote;
	int		in_double_quote;

	dst = str;
	src = str;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*src)
	{
		if (*src == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*src == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

void	replace_export_with_env(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (ft_strcmp(current->str, "export") == 0)
		{
			if (current->next == NULL || ft_strcmp(current->next->str, "|") == 0
				|| ft_strcmp(current->next->str, "<") == 0
				|| ft_strcmp(current->next->str, ">") == 0
				|| ft_strcmp(current->next->str, ">>") == 0
				|| ft_strcmp(current->next->str, "<<") == 0)
			{
				free(current->str);
				current->str = ft_strdup("env2");
			}
		}
		current = current->next;
	}
}

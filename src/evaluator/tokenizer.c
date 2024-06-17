/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:02:10 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 16:39:37 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// will be migrated to this function
// for now, just a placeholder
void	tokenizer(char *str)
{
	char	*line;
	char	**args;
	t_token	*token;
	char	**test;

	// first. we will replace spaces inside quotes
	// with a special character so that we can split
	// the string by spaces later without splitting
	// the words inside the quotes
	// for example, if the string is like this:
	// "hello world" "this is a test"
	// then the string will be modified to:
	// "hello^world" "this^is^a^test"
	replace_spaces_in_quotes(str);
	// second. we will split by double quotes
	// for example, if the string is like this:
	// "hello^world" "this^is^a^test"
	// then the string will be split into:
	// hello^world and this^is^a^test
	// and rejoined to: single array of strings
	// third. we will split by single quotes
	// for example, if the string is like this:
	// 'hello^world' 'this^is^a^test'
	// then the string will be split into:
	// hello^world and this^is^a^test
	// fourth. we will split by spaces
	// for example, if the string is like this:
	// hello^world and this^is^a^test
	// then the string will be split into:
	// hello^world, this^is^a^test
	replace_spaces_in_quotes(line);
	ft_printf("line: %s\n", line);
	args = ft_split(line, '"');
	// line = NULL;
	line = ft_rejoin_arr(args);
	ft_printf("line: %s\n", line);
	// args = ft_split(line, '\'');
	// line = ft_rejoin_arr(args);
	args = ft_split(line, ' ');
	///
	token = array_to_list(args);
	debug_print_list(token);
	///
	ft_printf("================\n");
	///
	// token = token_split_redirect(token);
	//		token = token_split_redirect(token);
	// evaluate_token_chain(token);
	// execute_command(token);
	// debug_print_list(token);
	///
	// ft_printf("================\n");
	///
	// test = lst_to_arr(token);
}

// this function will walk through the token chain
// if current token has valid quotes, it will remove
// the quotes from the token
// for example, if the token is like this:
// "hello world"
// then the token will be modified to:
// hello world
// also if the token is like this:
// 'hello world'
// then the token will be modified to:
// hello world
// but if the token is like this:
// "'hello world'"
// then the token will be modified to:
// 'hello world'
// also if the token is like this:
// "'hello world"
// then the token will be modified to:
// 'hello world

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
		{
			in_single_quote = !in_single_quote;
		}
		else if (*src == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		else
		{
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
}

void	fill_up_token_with_env(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		replace_env_vars(&current->str);
		current = current->next;
	}
}

void	replace_env_vars(char **str)
{
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
	char	*p;
	size_t	result_len;
	size_t	before_len;
	size_t	after_len;

	result = NULL;
	char *env_start, *env_end, *env_name, *env_value;
	in_single_quote = 0;
	in_double_quote = 0;
	p = *str;
	while (*p)
	{
		if (*p == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			p++;
			continue ;
		}
		else if (*p == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			p++;
			continue ;
		}
		else if (*p == '$' && !in_single_quote)
		{
			env_start = p + 1;
			env_end = env_start;
			while (*env_end && (*env_end == '_' || isalnum(*env_end)))
			{
				env_end++;
			}
			env_name = strndup(env_start, env_end - env_start);
			env_value = getenv(env_name);
			free(env_name);
			if (env_value)
			{
				result_len = result ? ft_strlen(result) : 0;
				before_len = p - *str;
				after_len = ft_strlen(env_end);
				result = realloc(result, result_len + before_len
						+ ft_strlen(env_value) + after_len + 1);
				if (result_len == 0)
				{
					strncpy(result, *str, before_len);
				}
				ft_strcpy(result + result_len + before_len, env_value);
				ft_strcpy(result + result_len + before_len
					+ ft_strlen(env_value), env_end);
				p = result + result_len + before_len + ft_strlen(env_value);
			}
			else
			{
				p = env_end;
			}
			continue ;
		}
		p++;
	}
	if (result)
	{
		free(*str);
		*str = result;
	}
}

void	replace_special_characters(char *str, char special_character)
{
	while (*str != '\0')
	{
		if (*str == special_character)
		{
			*str = ' ';
		}
		str++;
	}
}
// walk through the token chain and replace special characters
// with spaces
void	replace_special_characters_in_node(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		replace_special_characters(current->str, '^');
		current = current->next;
	}
}

// Helper function to create a new token node
// this one is just for token_split_redirect
t_token	*create_token_node(const char *str, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->str = ft_strdup(str);
	new->type = type;
	new->executed = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*split_token(t_token *token, char *pos, const char *redir,
		int redir_type)
{
	char	*before;
	char	*after;
	t_token	*before_token;
	t_token	*redirect_token;
	t_token	*after_token;

	// t_token	*redirect_token;
	// char	*after;
	if (pos != token->str) // Redirection is not at the beginning
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
			token = before_token; // Update head if it was the first token
		before_token->prev = token->prev;
		free(token->str);
		free(token);
		free(before);
		free(after);
		return (after_token);
	}
	else // Redirection is at the beginning
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
			token = redirect_token; // Update head if it was the first token
		return (token->next);
	}
}

// iterate through a token chain if found a special character
// inside the token, split the token into two token nodes
// and insert a new token node with the special character
// between the two token nodes and return the head of the
// token chain.

// example: "[echo] [>>hello.txt]" -> "[echo] [>>] [hello.txt]"
// return : "[echo] [>>] [hello.txt]"

// currently only for >> and <<

// Split the token and insert new token nodes as necessary

//
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

int	is_within_quotes(const char *str, const char *pos)
{
	int in_single_quote = 0;
	int in_double_quote = 0;

	for (const char *p = str; p < pos; p++)
	{
		if (*p == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*p == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
	}
	return (in_single_quote || in_double_quote);
}

// this function will check if string have quotes
// if it does, it will check any spaces inside the quotes
// and replace them with a special character
// so that we can split the string by spaces later
// without splitting the words inside the quotes
// for example, if the string is like this:

// "hello world" "this is a test"
// then the string will be modified to:
// "helloЙworld" "thisЙisЙaЙtest"

// this function will return the modified string

void	replace_spaces_in_quotes(char *str)



void	replace_spaces_in_quotes1(char *str)
{
	int		inside_single_quotes;
	int		inside_double_quotes;
	int		single_quote_count;
	int		double_quote_count;
	char	*ptr;

	inside_single_quotes = 0;
	inside_double_quotes = 0;
	single_quote_count = 0;
	double_quote_count = 0;
	ptr = str;
	// First pass to count quotes
	while (*ptr != '\0')
	{
		if (*ptr == '\'')
		{
			single_quote_count++;
		}
		else if (*ptr == '"')
		{
			double_quote_count++;
		}
		ptr++;
	}
	// Check if quotes are balanced
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
	{
		// Unbalanced quotes, do not replace spaces
		return ;
	}
	// Reset pointer for second pass
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '\'' && !inside_double_quotes)
		{
			inside_single_quotes = !inside_single_quotes;
		}
		else if (*ptr == '"' && !inside_single_quotes)
		{
			inside_double_quotes = !inside_double_quotes;
		}
		else if ((inside_single_quotes || inside_double_quotes) && *ptr == ' ')
		{
			*ptr = '^';
		}
		ptr++;
	}
}


// this function will remove empty nodes from the token chain
// for example, if the token chain is like this:
// "ls" -> "" -> "echo"
// then the chain will be modified to:
// "ls" -> "echo"

void	remove_empty_nodes(t_token *token)


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


// walk through the token chain and replace special characters
// with spaces
void	replace_special_characters_in_node(t_token *token)


// Helper function to create a new token node
// this one is just for token_split_redirect
t_token	*create_token_node(const char *str, int type)


t_token	*split_token(t_token *token, char *pos, const char *redir,
		int redir_type)
{
	char	*before;
	char	*after;
	t_token	*before_token;
	t_token	*redirect_token;
	t_token	*after_token;

	if (pos != token->str) // Redirection is not at the beginning
	{
		before = ft_strndup(token->str, pos - token->str);
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
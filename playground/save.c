
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

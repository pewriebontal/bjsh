
// this function walk through the token chain
// and split by special characters and add back
// to the new token chain
// for example: ls -la|wc -> would be come ls -la | wc
// and return the new token chain
// another example: ls -la >> >file -> would be come ls -la >> > file
// another example: ls -la >> >>file|wc -> would be come ls -la >> >> file | wc

// so it need to check current node's string and scan from the beginning
// to end of the string and check if there is any special characters
// if there is any special characters,
//	it will split the first part of the string
// and create a new token and add back to the new token chain and it's type

// rules:
// >> comes first than >
// dont split if string is in single quote or double quote

// Main function to walk through the token chain and split by special characters
t_token	*final_stage(t_token *token)
{
	t_token	*new_token;
	t_token	*current;

	new_token = NULL;
	current = token;
	while (current)
	{
		split_by_special_chars(current->str, &new_token);
		current = current->next;
	}
	clear_list(token);
	return (new_token);
}

// FINAL WORKING

void execute_tokens(t_token *head, t_bjsh *bjsh)
{
	if (head == NULL)
        return;
	t_execution_context context;
	context.current = head;
	context.in_fd = STDIN_FILENO;	// Initially, input comes from standard input
	context.out_fd = STDOUT_FILENO; // Initially, output goes to standard output
	context.command_found = find_command(context.current);

 	// If no commands are found, return without executing anything
	if (!context.command_found)
	{
		ft_dprintf(2, "🤌 ❯ syntax error near unexpected token `newline'\n");
		return;
	}

	// Reset current to head to start execution
	context.current = head;
	while (context.current != NULL)
	{
		char *args[MAX_ARGS]; // Assuming no command has more than 100 arguments
		context.argc = 0;
		// Collect arguments for the current command
		collect_arguments(&context.current, args, &context.argc);

		// Handle redirections before executing commands
		if (handle_redirections(&context, bjsh) == -1)
		{
			// If there's a redirection error, return immediately without executing
			return;
		}

		if (check_builtin(args[0]) == BUGGI_BAKA)
		{
			bjsh->last_exit_status = bjsh_exec_builtin(args, bjsh);
		}
		else if (context.current == NULL || context.current->type == PIPE)
		{
			// If we reach a pipe or the end of the chain, execute the command
			if (context.current != NULL)
				pipe(context.fd);
			execute_command_or_builtin(args, &context, bjsh);
			if (context.current != NULL)
			{
				close(context.fd[1]);
				context.in_fd = context.fd[0]; // Save the input for the next command
				context.current = context.current->next;
			}
		}
		else
		{
			// If we encounter an unsupported token type, just skip it
			context.current = context.current->next;
		}
	}

	// Close any remaining open file descriptors
	if (context.in_fd != STDIN_FILENO)
		close(context.in_fd);
	if (context.out_fd != STDOUT_FILENO)
		close(context.out_fd);
}
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


// Function to execute a single command
void	execute_command(t_token *tokens, char **envp)
{
	char	*args[256];
	int		i;
	char	*executable_path;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		args[i++] = tokens->str;
		tokens = tokens->next;
	}
	args[i] = NULL;
	if (check_builtin(args[0]))
	{
		bjsh_exec_builtin(args);
		return ;
	}
	executable_path = find_executable(args[0], envp);
	if (fork() == 0)
	{
		if (executable_path)
		{
			execve(executable_path, args, envp);
			perror("execve failed");
			exit(1);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
	free(executable_path);
}

// Function to handle redirection
void	handle_redirection(t_token **tokens)
{
	t_token	*current;
	int		fd;

	current = *tokens;
	if (current->type == REDIRECT_OUT_APPEND)
	{
		fd = open(current->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (current->type == REDIRECT_OUT)
	{
		fd = open(current->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (current->type == REDIRECT_IN)
	{
		fd = open(current->next->str, O_RDONLY);
	}
	else
	{
		return ;
	}
	if (fd < 0)
	{
		perror("open failed");
		exit(1);
	}
	if (current->type == REDIRECT_OUT || current->type == REDIRECT_OUT_APPEND)
	{
		dup2(fd, STDOUT_FILENO);
	}
	else if (current->type == REDIRECT_IN)
	{
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	*tokens = current->next->next;
}

// Function to handle pipes
void	handle_pipes(t_token *tokens, char **envp)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_command(tokens, envp);
		exit(1);
	}
	else
	{
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

// Function to find the full path of an executable
char	*find_executable44(const char *command, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*path;
	char	*executable_path;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_strdup(path_env);
	path = ft_strtok(paths, ":");
	executable_path = malloc(256);
	while (path)
	{
		snprintf(executable_path, 256, "%s/%s", path, command);
		if (access(executable_path, X_OK) == 0)
		{
			free(paths);
			return (executable_path);
		}
		path = ft_strtok(NULL, ":");
	}
	free(paths);
	free(executable_path);
	return (NULL);
}

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
	while (*ptr != '\0')
	{
		if (*ptr == '\'')
			single_quote_count++;
		else if (*ptr == '"')
			double_quote_count++;
		ptr++;
	}
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
		return ;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (*ptr == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else if ((inside_single_quotes || inside_double_quotes) && *ptr == ' ')
			*ptr = '`';
		ptr++;
	}
}

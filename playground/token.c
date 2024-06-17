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
#include <minishell.h>

t_token	*ft_new_token(int left_cmd, int right_cmd, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
    new->type = type;
	new->tmp_left = left_cmd;
    new->tmp_right = right_cmd;
	new->next = NULL;
	return (new);
}

t_token	*ft_last_token(t_token *token)
{
	if (token == NULL)
		return (0);
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void    ft_token_addback(t_token **token, t_token *new)
{
    t_token *tmp;

    if (*token)
    {
        tmp = ft_last_token(token);
        tmp->next = new;
    }
    else
        *token = new;
}

void    init_token(t_bjsh *bjsh,int type)
{
    //ft_find_cmd(t_bjsh *bjsh,int type);//find left and rignt cmds of the token symbol
   
    if (!bjsh->token)
    {
        bjsh->token = ft_new_token(1,1,type);
    }
    else
    {
        ft_token_addback(&bjsh->token,ft_new_token(1,1,type));
    }
}

void    set_token(t_bjsh *bjsh)
{   
    int i;

    i = 0;
    while (bjsh->argv[i])
    {
        if (bjsh->argv[i] == "|")
            init_token(bjsh, PIPE);
        if (bjsh->argv[i] == ">")
            init_token(bjsh, RDIR_R);
        if (bjsh->argv[i] == ">>")
            init_token(bjsh, RDIR_RR);
        if (bjsh->argv[i] == "<<")
            init_token(bjsh, RDIR_L);
        if (bjsh->argv[i] == ";")
            init_token(bjsh, END);
        i++;
    }
}
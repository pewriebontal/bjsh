#include <minishell.h>

void    init_token(t_bjsh *bjsh)
{
    bjsh->token->pipe = 0;
    bjsh->token->redir_right = 0;
    bjsh->token->redir_left = 0;
    bjsh->token->end = 0;
}

void    count_token(t_bjsh *bjsh)
{
    printf("\nValue >>%s<<\n",bjsh->argv);
    
    int i;

    i = 0;
    while (bjsh->argv[i])
    {
        if (bjsh->argv[i] == "|")
            bjsh->token->pipe++;
        if (bjsh->argv[i] == ">>")
            bjsh->token->redir_right++;
        if (bjsh->argv[i] == ">")
            bjsh->token->redir_right++;  
        if (bjsh->argv[i] == "<<")
            bjsh->token->redir_left++;
        if (bjsh->argv[i] == ";")
            bjsh->token->end++;
        i++;
    }
}

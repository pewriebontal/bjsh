#include <minishell.h>

t_token   *new_token(char *cmd)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->str = strdup(cmd);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_token   *update_token(t_token *old_cmd, t_token *new_cmd)
{
    old_cmd->next = new_cmd;
    new_cmd->prev = old_cmd;
    return (old_cmd);
}

void    print_token(t_token *cmd)
{
    t_token *tmp;

    tmp = cmd;

    //reset the header node 
    while (tmp->prev)
        tmp = tmp->prev;

    while (tmp)
    {
        printf("%s\n", tmp->str);
        tmp = tmp->next;
    }
}

void	free_token(t_token **cmd)
{
	t_token	*tmp;
	t_token	*next;

	if (!cmd)
		return ;
	tmp = *cmd;
    //reset the header node 
    while (tmp->prev)
        tmp = tmp->prev;
	while (tmp)
	{
		next = tmp->next;
        free(tmp);
		tmp = next;
	}
	*cmd = NULL;
}

//replace with env variabel
char    *expand_env(char *arr)
{
    int     len;
    char    *env_arr;

    env_arr = (char *)malloc(sizeof(char *) * 1024);
    if (*arr == '$')
    {
        *arr++;
        ft_strlcpy(env_arr,arr,sizeof(env_arr));
        return (getenv(env_arr));
    }
    return (arr) ;
}

//get the avg and change to list
int set_token_list(t_bjsh *bjsh, char *arr)
{
    int i;
    int q;
    
    t_token *token;
    t_token *tmp_token;

    //char *arr = {"ls -a | grep e | wc -l"};
    
    char *tmp_arr;
    int arr_len;

    token = NULL;
   
   // -->with history file 
    arr_len = ft_strlen(arr);
    i = 0;
    while (i <= arr_len)
    {
        //for quote
        //need to check the ptr of arr
        if (arr[i] == '"')
        {
            q = 1;//+i
            i++;//change ptr
            while (arr[i] != '"')
            {
                i++;
                q++;
                if (q > arr_len)//need to check
                {
                    perror("can't find end quot");
                    exit(EXIT_FAILURE);
                }
            }
            tmp_arr = (char *)malloc(sizeof(char *) * q - 1);// reduce place for << " >>
            *arr++;//to avoid the starting << " >>
            tmp_arr = ft_strncpy(tmp_arr,arr,q - 1);
            if (!token)
                token = new_token(tmp_arr);
            else
            {
                tmp_token = new_token(tmp_arr);
                while (token->next)
                    token = token->next;
                token = update_token(token, tmp_token);
            }
            arr += i + 1;
            arr_len -= i + 1;
            i = 0;
            free(tmp_token);
        }


        //for normal
        if (arr[i] == ' ' || arr[i] == '|' || i == arr_len )
        {
            tmp_arr = (char *)malloc(sizeof(char) * i + 1);
            tmp_arr = strndup(arr, i);
            if (!token)
                token = new_token(expand_env(tmp_arr));
            else
            {
                tmp_token = new_token(expand_env(tmp_arr));
                while (token->next)
                    token = token->next;
                token = update_token(token, tmp_token);
            }
            arr += i + 1;
            arr_len -= i + 1;
            i = 0;
            free(tmp_token);
        }
        i++;
    }
    print_token(token);
    
    // --> with user input
    // i = 1;
    // if (ac < 2)
    //     return (-1);
    
    // while(av[i] != NULL)
    // {   
    //     if (!cmd)
    //        cmd = new_cmd(av[i]); 
    //     else
    //     {
    //         t_cmd *tmp;
    //         tmp = new_cmd(av[i]);
    //         while (cmd->next)//set to the last node
    //             cmd = cmd->next;
    //         cmd = add_cmd(cmd, tmp);
    //     }
    //     //reset ptr to head
    //     while (cmd->prev)
    //         cmd = cmd->prev;
    //     i++;
    // }
    // print_cmd(cmd);
    // free_cmd(&cmd);
    return (0);
}
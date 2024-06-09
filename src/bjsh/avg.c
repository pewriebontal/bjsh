#include <minishell.h>

t_avg   *new_avg(char *cmd)
{
    t_avg *new;

    new = (t_avg *)malloc(sizeof(t_avg));
    if (!new)
        return (NULL);
    new->str = strdup(cmd);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_avg   *add_avg(t_avg *old_cmd, t_avg *new_cmd)
{
    old_cmd->next = new_cmd;
    new_cmd->prev = old_cmd;
    return (old_cmd);
}

void    print_avg(t_avg *cmd)
{
    t_avg *tmp;

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

void	free_avg(t_avg **cmd)
{
	t_avg	*tmp;
	t_avg	*next;

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

//get the avg and change to list
int set_avg_list(t_bjsh *bjsh)
{
    int i;
    t_avg *cmd;
    t_avg *tmp;

    char *arr = {"ls -a | grep e | wc -l"};
    char *tmp_avg;
    int arr_len;

    cmd = NULL;
   
   // -->with history file 
    arr_len = strlen(arr);
    i = 0;
    while (i <= arr_len)
    {
        if (arr[i] == ' ' || arr[i] == '|' || i == arr_len )
        {
            tmp_avg = (char *)malloc(sizeof(char) * i + 1);
            tmp_avg = strndup(arr, i);
            if (!cmd)
                cmd = new_avg(tmp_avg);
            else
            {
                tmp = new_avg(tmp_avg);
                while (cmd->next)
                    cmd = cmd->next;
                cmd = add_avg(cmd, tmp);
            }
            arr += i + 1;
            arr_len -= i + 1;
            i = 0;
            free(tmp_avg);
        }
        i++;
    }
    print_avg(cmd);
    
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
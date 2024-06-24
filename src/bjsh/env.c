/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klinn <klinn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:04:35 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 19:56:33 by klinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Function to append a new node to the end of the environment list
void	append_env_node(t_env **head, t_env *new_node)
{
	t_env	*tail;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tail = *head;
	while (tail->next != NULL)
	{
			tail = tail->next;
	}
		//tail =tail->next;
	tail->next = new_node;
	new_node->prev = tail;
	new_node->next = NULL;
}

// Function to create the environment list from envp
// void	create_env_list(t_bjsh *bjsh, t_env **head, t_env **tail)
// {
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	t_env	*new_node;

// 	i = 0;
// 	while (bjsh->envp[i])
// 	{
// 		key = NULL;
// 		value = NULL;
// 		split_env(bjsh->envp[i], &key, &value);
// 		new_node = create_env_node(key, value);
// 		free(key);
// 		free(value);
// 		if (!new_node)
// 			return ;
// 		if (!*head)
// 		{
// 			*head = new_node;
// 			//*tail = new_node;
// 		}
// 		else
// 		{
// 			append_env_node(tail, new_node);
// 			*tail = new_node;
// 		}
// 		i++;
// 	}
// }

t_env	*ft_envlast(t_env *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}


void	add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (*lst)
	{
		temp = ft_envlast(*lst);
		temp->next = new;
	}
	else
		*lst = new;
}


t_env	*create_env_list(t_bjsh *bjsh)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*tmp;
	t_env	*head;

	head = NULL;
	i = 0;
	while (bjsh->envp[i])
	{
		key = NULL;
		value = NULL;
		split_env(bjsh->envp[i], &key, &value);
		if (!head)
		{
			head = create_env_node(key, value);
			free(key);
			free(value);
		}
		else
		{
			tmp = (t_env *)malloc (sizeof(malloc));
			tmp = create_env_node(key, value);
			add_back(&head,tmp);
			free(key);
			free(value);
		}
		i++;
	}
	return (head);
}

// Function to initialize the bjsh environment linked list
void	bjsh_env_init(t_bjsh *bjsh)
{
	t_env	*head;
	t_env	*tail;

	head = NULL;
	tail = NULL;
	if (!bjsh || !bjsh->envp)
		return ;
	initialize_env_list(&head, &tail);
	head = create_env_list(bjsh);
	bjsh->env = head;
}

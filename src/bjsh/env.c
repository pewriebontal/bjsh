#include <minishell.h>

//test
void show_env(t_bjsh *bjsh)
{
    printf("\n#start_TEST#\n");
    while (bjsh->env)
    {
        printf("\n-->%s",bjsh->env->value);
        bjsh->env = bjsh->env->next;
    }
    printf("\n#end_TEST#\n");
}

int init_env(t_bjsh *bjsh,char **env_avg)
{
    t_env	*env;
	t_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_env))))
		return (-1);
	env->value = ft_strdup(env_avg[1]);
	env->next = NULL;
	bjsh->env = env;
	i = 1;
	while (env_avg[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (-1);
		new->value = ft_strdup(env_avg[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
    show_env(bjsh);
	return (0);
}
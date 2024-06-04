#include <minishell.h>

// test
void	show_env(t_bjsh *bjsh)
{
	//	printf("\n#start_TEST#\n");
	//	while (bjsh->env)
	//	{
	//		printf("\n-->%s", bjsh->env->value);
	//		bjsh->env = bjsh->env->next;
	//	}
	//	printf("\n#end_TEST#\n");
}

// var_name (e.g)USER, DBUS, ....
// chg_value -- the value that u want to chg with
void	chg_value_of_env(t_bjsh *bjsh, char *var_name, char *chg_value)
{
	//	int		i;
	//	int		j;
	//	char	*tmp;
	//
	//	while (bjsh->env)
	//	{
	//		if (ft_strncmp(bjsh->env->value, var_name, sizeof(var_name)) == 0)
	//		{
	//			i = 0;
	//			j = 0;
	//			while (bjsh->env->value[i + 1] != '=')
	//			{
	//				i++;
	//			}
	//			// still thinking......
	//		}
	//		bjsh->env = env->next;
	//	}
}

int	init_env(t_bjsh *bjsh, char **env_avg)
{
	//	t_env *env;
	//	t_env *new;
	//	int i;
	//
	//	if (!(env = malloc(sizeof(t_env))))
	//		return (-1);
	//	env->value = ft_strdup(env_avg[1]);
	//	env->next = NULL;
	//	bjsh->env = env;
	//	i = 1;
	//	while (env_avg[i])
	//	{
	//		if (!(new = malloc(sizeof(t_env))))
	//			return (-1);
	//		new->value = ft_strdup(env_avg[i]);
	//		new->next = NULL;
	//		env->next = new;
	//		env = new;
	//		i++;
	//	}
	//	show_env(bjsh);
	//	return (0);
}
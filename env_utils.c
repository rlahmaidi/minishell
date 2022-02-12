#include "minishell.h"

char *ft_strjoin_free(char *k,char *val)
{
	char *tmp;

	tmp = ft_strjoin(k, val);
	free(k);
	return(tmp);
}

char **list_to_env(t_node *node)
{
	char	**env_tab;
	t_node	*tmp;
	int		i;
	int		j;

	tmp = node;
	//start of list_size
	i = 0;
	while(tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	//end of list_size;
	env_tab = malloc(sizeof(char *) * (i + 1));
	j = 0;
	tmp = node;
	while(i-- > 0)
	{
		env_tab[j] = ft_strjoin(tmp->name, "=");
		env_tab[j] = ft_strjoin_free(env_tab[j], tmp->val);
		j++;
		tmp = tmp->next;
	}
	env_tab[j] = NULL;
	return(env_tab);
}

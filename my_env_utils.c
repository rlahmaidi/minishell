/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:52:34 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 02:52:59 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *k, char *val)
{
	char	*tmp;

	tmp = ft_strjoin(k, val);
	free(k);
	return (tmp);
}

char	**node_to_table(t_node *node, char **env_tab, int i)
{
	t_node	*tmp;
	char	*temp;
	int		j;

	tmp = node;
	j = 0;
	while (i-- > 0)
	{
		if (tmp->val[0] == '=')
		{
			env_tab[j] = ft_strjoin(tmp->name, "=");
			temp = ft_strtrim(tmp->val + 1, "\"");
			env_tab[j] = ft_strjoin_free(env_tab[j], temp);
			free(temp);
			j++;
		}
		tmp = tmp->next;
	}
	env_tab[j] = NULL;
	return (env_tab);
}

char	**list_to_env(t_node *node)
{
	char	**env_tab;
	t_node	*tmp;
	int		i;

	tmp = node;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	env_tab = node_to_table(node, env_tab, i);
	return (env_tab);
}

t_node	*search_for_env(t_node *node, char *env)
{
	t_node	*tmp;

	tmp = node;
	while (tmp != NULL && ft_strcmp(tmp->name, env))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

char	*chage_derictory(char *args, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (args != NULL)
	{
		tmp = ft_strdup(args);
		if (chdir(args) == -1)
			printf("cd: no such file or directory: %s\n", args);
	}
	else
	{
		tmp = ft_substr(str, 2, ft_strlen(str) - 3);
		if (chdir(tmp) == -1)
			printf("cd: no such file or directory: %s\n", tmp);
	}
	return (tmp);
}

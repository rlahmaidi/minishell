/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtins_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:54:11 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 16:29:10 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(char **args, t_node *node)
{
	char	*tmp;
	t_node	*tmp1;
	char	*old_pwd;
	char	*tmp2;

	tmp = NULL;
	tmp1 = NULL;
	tmp1 = search_for_env(node, "HOME");
	tmp = chage_derictory(args[1], tmp1->val);
	if (!search_for_env(node, "PWD"))
		add_node("PWD=test", node);
	tmp1 = search_for_env(node, "PWD");
	old_pwd = ft_substr(tmp1->val, 0, ft_strlen(tmp1->val));
	tmp2 = add_char_beggin(tmp, '"', 0);
	free(tmp1->val);
	tmp1->val = add_char_beggin(tmp2, '=', 1);
	tmp1->val = add_char_end(tmp1->val, '"', 1);
	tmp1 = search_for_env(node, "OLDPWD");
	free(old_pwd);
	free(tmp);
	return (0);
}

int	my_pwd(char **args, t_node *node)
{
	char	*strpwd;

	(void)node;
	(void)args;
	strpwd = getcwd(NULL, 0);
	printf("%s\n", strpwd);
	free(strpwd);
	return (1);
}

int	my_env(char **args, t_node *node)
{
	t_node	*tmp;
	int		i;
	char	**temp;

	tmp = node;
	temp = list_to_env(tmp);
	i = -1;
	if (args[1])
	{
		printf("env: %s: No such file or directorys\n", args[1]);
		return (0);
	}
	while (temp[++i])
		printf("%s\n", temp[i]);
	i = 0;
	while (temp[i])
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
	return (0);
}

void	set_node(char arg, t_node *new_node)
{
	char	*p;

	if (arg == '=')
	{
		new_node->val = add_char_beggin(new_node->val, '"', 1);
		new_node->val = add_char_end(new_node->val, '"', 1);
		p = new_node->val;
		new_node->val = ft_strjoin("=", new_node->val);
		free(p);
	}
}

int	add_node(char *args, t_node *node)
{
	t_node	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_node));
	while (args[i] && args[i] != '=')
		i++;
	new_node->name = ft_substr(args, 0, i);
	new_node->val = ft_substr(args, i + 1, ft_strlen(args));
	if (new_node->val == NULL && args[i] == '=')
		new_node->val = ft_strdup("");
	while (node->next != NULL)
	{
		if (node_exist(args, node, i, new_node))
			return (0);
		else
			node = node->next;
	}
	if (node_exist(args, node, i, new_node))
		return (0);
	set_node(args[i], new_node);
	node->next = new_node;
	new_node->next = NULL;
	return (0);
}

void	print_export(char *arg, t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (!arg)
	{
		while (tmp)
		{
			printf("declare -x ");
			printf("%s", tmp->name);
			if (tmp->val != NULL)
				printf("%s", tmp->val);
			printf("\n");
			tmp = tmp->next;
		}
	}
}

int	my_export(char **args, t_node *node)
{
	int		i;

	print_export(args[1], node);
	if (args[1])
	{
		i = 0;
		while (args[++i])
		{
			if (isvalid_var_export(args[i]) == -1)
			{
				ft_export_errors(args[i++]);
				continue ;
			}
			else
				add_node(args[i], node);
		}
	}
	return (0);
}

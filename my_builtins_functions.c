#include "minishell.h"

int	my_cd(char **args, t_node *node)
{
	char	*tmp;
	t_node	*tmp1;

	tmp = NULL;
	tmp1 = node;
	while (tmp1 != NULL && ft_strcmp(tmp1->name, "HOME"))
	{
		tmp1 = tmp1->next;
	}
	if (args[1] != NULL)
	{
		tmp = ft_strdup(args[1]);
		if (chdir(args[1]) == -1)
			printf("cd: no such file or directory: %s\n", args[1]);
	}
	else
	{
		tmp = ft_substr(tmp1->val, 2, ft_strlen(tmp1->val) - 3);
		if (chdir(tmp) == -1)
			printf("cd: no such file or directory: %s\n", args[1]);
		tmp = ft_strdup(tmp1->val);
	}
	tmp1 = node;
	while (tmp1 != NULL && ft_strcmp(tmp1->name, "PWD"))
	{
		tmp1 = tmp1->next;
	}
	tmp1->val = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;// i don't remember why?? i think it was to avoid the double free;
	return (0);
}

int	my_pwd(char **args, t_node *node)
{
	(void)node;
	(void)args;
	printf("%s\n", getcwd(NULL, 0));
	return (1);
}

int	my_env(char **args, t_node *node)
{
	t_node	*tmp;

	(void)args;
	tmp = node;
	while (tmp != NULL)
	{
		if (tmp->val)
		{
			printf("%s", tmp->name);
			printf("%s\n", tmp->val);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	add_node(char *args, t_node *node)
{
	t_node	*new_node;           // only one error left to fix,
	int		i;						//expot a="";

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
	//could be the start of a function for norm;
	
	if (args[i] == '=')
	{
		new_node->val = add_char_beggin(new_node->val, '"');
		new_node->val = add_char_end(new_node->val, '"');
		new_node->val = ft_strjoin("=",new_node->val);// i added this line ;
	}
	node->next = new_node;
	new_node->next = NULL;
	//end for norm;
	return (0);
}

int	my_export(char **args, t_node *node)
{
	int		i;		//ERROR TO BE FIXED;
	t_node	*tmp;// when a new env is exported and listed with the env commend the "="
						// dosen't show up;
	tmp = node;
	if (args[1] == NULL)
	{
		while (tmp != NULL)
		{
			printf("declare -x ");
			printf("%s", tmp->name);
			if (tmp->val != NULL)
				printf("%s", tmp->val);
			printf("\n");
			tmp = tmp->next;
		}
	}
	else
	{
		i = 1;
		while (args[i])
		{
			if (!ft_isalpha(args[i][0]))
				printf("%s: not a valid identifier\n", args[i]);
			else
				add_node(args[i], node);
			i++;
		}
	}
	return (0);
}

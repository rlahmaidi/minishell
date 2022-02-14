#include "minishell.h"

int	my_cd(char **args, t_node *node)
{
	char	*tmp;
	t_node	*tmp1;
	char	*old_pwd;
	
	tmp = NULL;
	tmp1 = NULL;
	tmp1 = search_for_env(node, "HOME");
	tmp = chage_derictory(args[1], tmp1->val);
	tmp1 = search_for_env(node,"PWD");
	old_pwd = ft_substr(tmp1->val, 0, ft_strlen(tmp1->val));
	tmp1->val = add_char_beggin(tmp,'"');
	tmp1->val = add_char_beggin(tmp1->val,'=');
	tmp1->val = add_char_end(tmp1->val,'"');
	tmp1 = search_for_env(node, "OLDPWD");
	tmp1->val = ft_strdup(old_pwd);// this is goooood;but ft_strdup may cause leaks;
	free(old_pwd);
	free(tmp);
	tmp = NULL;
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
	char	*str;

	(void)args;// ERROR :i print node->val with the "" but the bash dosen't;
	tmp = node;
	while (tmp != NULL)
	{
		if (tmp->val)
		{
			printf("%s", tmp->name);
			str = ft_substr(tmp->val, 2, ft_strlen(tmp->val) - 3);
			printf("=%s\n", str);
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
			if (isvalid_var_export(args[i]) == -1)
			{
				ft_export_errors(args[i]);
				i++;
				continue;
			}
			else
				add_node(args[i], node);
			i++;
		}
	}
	return (0);
}

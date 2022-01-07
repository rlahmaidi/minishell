#include "minishell.h"


int my_cd(char **args, t_node *node)
{
	(void)args;
	char *tmp;
	t_node *tmp1;

	tmp = NULL;
	tmp1 = node;
	check_cd_errors(args);
	while(tmp1 != NULL && ft_strcmp(tmp1->name, "HOME"))
	{
		tmp1 = tmp1->next;
	}
	if(args[1] != NULL)
	{
		tmp = ft_strdup(args[1]);
		if(chdir(args[1]) == -1)
			printf("no such file or directory: %s\n",args[1]);
	}
	else
	{
		tmp = ft_substr(tmp1->val, 2, ft_strlen(tmp1->val) - 3);
		if(chdir(tmp) == -1)
			printf("no such file or directory: %s\n",args[1]);
		tmp = ft_strdup(tmp1->val);
	}
	tmp1 = node;
	while(tmp1 != NULL && ft_strcmp(tmp1->name, "PWD"))
	{
		tmp1 = tmp1->next;
	}
	tmp1->val = ft_strdup(tmp);
	free(tmp);
	tmp =NULL;
	return (0);
}

int my_pwd(char **args, t_node  *node)
{
	(void)node;
	(void)args;
	printf("%s\n", getcwd(NULL, 0));
	return(1);
}

int my_env(char **args, t_node *node)
{
	t_node	*tmp;

	(void)args;
	tmp = node;
	while(tmp != NULL)
	{
		if (tmp->val)
		{
			printf("%s",tmp->name);
			printf("%s\n",tmp->val);
		}
		tmp = tmp->next;
	}
	return(1);
}

int add_node(char *args, t_node *node)
{
	t_node *new_node;
	int i;

	i = 0;
	new_node = malloc(sizeof(t_node));
	
	while(args[i] && args[i] != '=')
		i++;
	new_node->name = ft_substr(args, 0 , i);
	new_node->val = ft_substr(args, i + 1, ft_strlen(args));
	while(node->next != NULL)
	{
		if(!ft_strcmp(node->name,new_node->name))
		{ 
			if( args[i] == '=')
			{
				new_node->val = add_char_beggin(new_node->val, '"');
				new_node->val = add_char_end(new_node->val, '"');
				node->val = new_node->val;
				return(0);
			}
			else
				return(1);
		}
		node = node->next;
	}
	new_node->val = add_char_beggin(new_node->val, '"');
	new_node->val = add_char_end(new_node->val, '"');
	node->next = new_node;
	new_node->next = NULL;
	return(0);
}

int my_export(char **args,t_node *node)
{
	int		i;
	t_node	*tmp;

	// (void)args;
	// (void)node;
	tmp = node;
	if(args[1] == NULL)
	{
		while(tmp != NULL)
		{	
			printf("declare -x ");
			printf("%s=",tmp->name);
			printf("%s\n",tmp->val);
			tmp = tmp->next;
		}
	}
	else
	{
		i = 1;
		while(args[i])
		{
			if(!ft_isalpha(args[i][0]))
				printf("%s: not a valid identifier\n", args[i]);
			else
				add_node(args[i],node);
			i++;
		}
	}
	return(0);
}

int my_unset(char **args,t_node *node)
{
	
	(void)args;
	(void)node;
	while(node)
	{

	}
	// if it needs the node argument it's ok, if not it's not gonna be with the first three at teh same
	//functions table;
	return (1);
}

int my_echo(char **args, t_node *node)
{
	int i;
	i = 1;
	(void)node;
	if(!ft_strcmp(args[1], "-n"))
	{
		i = 2;
		while (args[i])								//temporarelly commented;
		{
			printf("%s ",args[i]);
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			printf("%s ",args[i]);
			i++;
		}
		printf("\n");
	}
	return(1);
	//same for the above;
}



int my_exit(char **args, t_node *node)
{
		(void)node;
		printf("exit\n");
		if(count_args(args) == 1)
			exit(0);
		if(is_num(args[1]))
		{
			if(count_args(args) > 2)
			{
				printf("exit: too many argument\n");
				return(1);
			}
			else if ( count_args(args) == 2)
			{
				exit(ft_atoi(args[1]));
			}
		}
		else
		{
			printf("exit: %s: numeric argument required",args[1]);
			exit(255);
		}
		return(0);
}
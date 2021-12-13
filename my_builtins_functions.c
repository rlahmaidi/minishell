#include "minishell.h"

int my_cd(char **args, t_node *node)
{
	// i beiliever when changing the derictory i should change pwd in env
	//since we have our own env, an we we will need it later in my_pwd;
	//NOTE : we need nodes here to;
}

int my_pwd(char **args, t_node  *node)
{
	t_node *tmp;
	

	tmp = node;
	while(tmp->next != NULL)
	{
		if(tmp->name == "PWD")
			printf("%s",tmp->val);
		tmp = tmp->next;
	}
	if(tmp->name == "PWD")
		printf("%s",tmp->val);
	//serch for pwd value in the lists of noedes send by the parser;
	// NOTE:i didn't use argument;
	return(1);
}

int my_env(char **args, t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while(tmp->next != NULL)
	{
		printf("%s=",tmp->name);
		printf("%s",tmp->val);
		tmp = tmp->next;
	}
	printf("%s=",tmp->name);
	printf("%s",tmp->val);
	// just print the content of the list of nodes but you gonna need node as argument;
	//NOTE:i didn't use argument
	return(1);
}

int my_export(char **args,t_node *node)
{
	t_node	*tmp;
	char	*str;
	int		i;
	int j;

	tmp = NULL;
	i = 0;
	str = NULL;
	while(args[j][i])
	{
		while(args[j][i] && args[j][i] != '=')
		{
			str[i] = args[j][i];
			i++;
		}
		if(args[j][i] == '=')
		{
			i++;
			j = 0;
			*tmp->name = *str;//not sure if it should be the address or the value;
			str = NULL;
			while(args[j][i])
			{
				str[j] = args[j][i];
				i++;
			}
			tmp->val = str;
			tmp->next = node;
			node->next = tmp;
		}

		else
			return(1);
		j++;
	}

	// i don't know wether we should do error management or not???????????
	// if it needs the node argument it's ok, if not it's not gonna be with the first three at teh same
	//functions table;
}

int my_unset(char **args,t_node *node)
{
	while(node)
	{
		
	}
	//same for the above
}

int my_echo(char **args)
{
	if(args[1] == "-n")
	{
		//?????????
	}
	else
		printf("%s",args[1]);
	return(1);
	//same for the above;
}

int my_exit(char **args)
{
	return(1);
	// same for the above;
}
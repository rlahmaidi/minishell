#include "minishell.h"

int my_cd(char **args, t_node *node)
{
	(void)args;
	char *tmp;
	t_node *tmp1;

	tmp = NULL;
	tmp1 = node;
	while(tmp1 != NULL && ft_strcmp(tmp1->name, "HOME"))
	{
		tmp1 = tmp1->next;
		printf("%s\n",tmp1->val);
	}
	tmp = cut_equal(tmp1->val);
	printf("%s\n",tmp);
	if(args[1] != NULL)
	{
		tmp = args[1];
	}
	chdir(tmp);
	// i believe when changing the derictory i should change pwd in env
	//since we have our own env, an we we will need it later in my_pwd;
	//that's why i'm adding the below code;
	tmp1 = node;
	while(tmp1 != NULL && ft_strcmp(tmp1->name, "PWD"))
	{
		tmp1 = tmp1->next;
	}
	tmp1->val = tmp;
	return (1);
}

int my_pwd(char **args, t_node  *node)
{
	//t_node *tmp;
	(void)node;
	(void)args;
	// tmp = node;
	// if(args != NULL || args == NULL)// this if just to silence an error but it is still right
	// {								// since pwd in bash dosen't care about argument;
	// 	while(tmp != NULL && ft_strcmp(tmp->name, "PWD"))
	// 	{
	// 		tmp = tmp->next;
	// 	}
	// 	printf("%s\n",tmp->val);
	// }
	//char *s = getcwd();

	printf("%s\n", getcwd(NULL, 0));
	//serch for pwd value in the lists of noedes send by the parser;
	// NOTE:i didn't use argument;
	return(1);
}

int my_env(char **args, t_node *node)
{
	t_node	*tmp;

	(void)args;
	tmp = node;
	while(tmp != NULL)
	{	
		//printf("declare -x ");
		if (tmp->val)
		{
		printf("%s=",tmp->name);
		printf("%s\n",tmp->val);
		}
		tmp = tmp->next;
	}
	// just print the content of the list of nodes but you gonna need node as argument;
	//NOTE:i didn't use argument
	return(1);
}

void add_node(char *args, t_node *node)
{
	t_node *new_node;
	int i;

	// start of fill node
	i = 0;
	new_node = NULL;
	while(args[i] && args[i] != '=')
	{
		new_node->name[i] = args[i];
		i++;
	}
	//new_node->val = NULL;// i don't know wether i should initialize it or not;
	if(args[i] == '=')
	{
		while(args[i])
		{
			new_node->val[i] = args[i];
			i++;
		}
	}
	//end of fill_node() if nedded for norminette;
	while(node->next != NULL)
	{
		node = node->next;
	}
	node->next = new_node;
	new_node->next = NULL;
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
				printf("%s: not a valid identifier", args[i]);
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
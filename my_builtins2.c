#include "minishell.h"


int	isvalid_var(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (-1);
	i = 1;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	my_echo(char **args, t_node *node)
{
	int	i;

	i = 1;
	(void)node;
	if (!ft_strcmp(args[1], "-n"))
	{
		i = 2;
		while (args[i])
		{
			printf("%s ", args[i]);
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			printf("%s ", args[i]);
			i++;
		}
		printf("\n");
	}
	return (1);
}

int	my_exit(char **args, t_node *node)
{
	(void)node;
	printf("exit\n");
	if (count_args(args) == 1)
		exit(0);
	if (is_num(args[1]))
	{
		if (count_args(args) > 2)
		{
			printf("exit: too many argument\n");
			return (1);
		}
		else if (count_args(args) == 2)
		{
			exit(ft_atoi(args[1]));
		}
	}
	else
	{
		printf("exit: %s: numeric argument required", args[1]);
		exit(255);
	}
	return (0);
}

void	ft_export_errors(char *identifier)
{
	write(2, "minishell: export ", ft_strlen("minishell: export "));
	write(2, identifier, ft_strlen(identifier));
	write(2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier") + 1);
}

t_node *ft_remove_node(t_node *node, t_node *remove)
{
	t_node *tmp;
	t_node *next;
	
	if (node == remove)
	{
		tmp = node->next;
		free(node);
		return (tmp);
	}
	tmp = node;
	while (tmp)
	{
		if (tmp->next && (strcmp(tmp->next->name, remove->name) == 0))
		{
			next = tmp->next;
			tmp->next = tmp->next->next;
			free(next);
			return (node);
		}
		tmp = tmp->next;
	}
	return (node);
}

int	my_unset(char **args, t_node *node)
{
	int		i;
	int 	sign;
	t_node	*tmp;

	// start of check_error;
	i = 1;// it may be 0;
	sign = 0;
	while (args[i] != NULL)
	{
		if (isvalid_var(args[i]) == -1)
		{
			ft_export_errors(args[i]);
			sign = -1;
			continue;
		}
		tmp = node;
		while (tmp != NULL)
		{
			if(ft_strcmp(tmp->name, args[i]) == 0)
			{
				node = ft_remove_node(node, tmp);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (sign);
}

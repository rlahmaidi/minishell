/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:55:24 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 15:44:46 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(char **args, t_node *node)
{
	int	i;

	i = 1;
	(void)node;
	if (args[1] && !ft_strcmp(args[1], "-n"))
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
		exit(g_ret);
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

void	my_free_node(t_node *node)
{
	free(node->val);
	free(node->name);
	free(node);
}

t_node	*ft_remove_node(t_node *node, t_node *remove)
{
	t_node	*tmp;
	t_node	*next;

	if (node == remove)
	{
		tmp = node->next;
		my_free_node(node);
		return (tmp);
	}
	tmp = node;
	while (tmp)
	{
		if (tmp->next && (strcmp(tmp->next->name, remove->name) == 0))
		{
			next = tmp->next;
			tmp->next = tmp->next->next;
			my_free_node(next);
			return (node);
		}
		tmp = tmp->next;
	}
	return (node);
}

int	my_unset(char **args, t_node *node)
{
	int		i;
	t_node	*tmp;

	i = 0;
	g_ret = 0;
	while (args[++i] != NULL)
	{
		if (isvalid_var_unset(args[i]) == -1)
		{
			ft_unset_errors(args[i++]);
			g_ret = -1;
			continue ;
		}
		tmp = node;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->name, args[i]) == 0)
			{
				node = ft_remove_node(node, tmp);
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (g_ret);
}

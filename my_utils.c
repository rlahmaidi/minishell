/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:14:20 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 03:14:23 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (*(args + i))
	{
		i++;
	}
	return (i);
}

int	check_cd_errors(char **args)
{
	if (args[3])
	{
		printf ("cd: too many argumrnts\n");
		return (2);
	}
	if (args[2])
	{
		printf ("cd: string not in pwd: %s\n", args[1]);
		return (1);
	}
	return (0);
}

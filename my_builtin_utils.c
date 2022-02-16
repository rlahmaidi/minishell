/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:32:27 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 15:38:04 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isvalid_var_unset(char *str)
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

int	isvalid_var_export(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (-1);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_unset_errors(char *identifier)
{
	write(2, "minishell: unset ", ft_strlen("minishell: unset "));
	write(2, identifier, ft_strlen(identifier));
	write(2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier") + 1);
}

void	ft_export_errors(char *identifier)
{
	write(2, "minishell: export ", ft_strlen("minishell: export "));
	write(2, identifier, ft_strlen(identifier));
	write(2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier") + 1);
}

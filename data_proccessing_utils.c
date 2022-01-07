/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proccessing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:29:12 by zoizmer           #+#    #+#             */
/*   Updated: 2021/12/05 22:29:15 by zoizmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_val(char	*name, t_node	*node)
{
	char	*ret;

	ret = NULL;
	while (node != NULL)
	{
		if (!ft_strncmp(name, node->name, ft_strlen(name) + 1))
		{
			ret = ft_strdup(node->val);
			break ;
		}
		node = node->next;
	}
	if (ret == NULL)
		ret = ft_strdup("");
	return (ret);
}

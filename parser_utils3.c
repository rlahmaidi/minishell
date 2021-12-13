/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:29:01 by zoizmer           #+#    #+#             */
/*   Updated: 2021/12/05 22:29:03 by zoizmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**splitargs(char	*str)
{
	char	**ret;
	int		size;
	int		i;
	int		r;

	size = sizelen(str, 0, 0, 0);
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	r = 0;
	while (i < size)
	{
		ret[i] = get_arg(str, &r);
		i++;
	}
	ret[size] = NULL;
	return (ret);
}

t_cmd	*alloc_cmd_s(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (0);
	ret->args = NULL;
	ret->cmd = NULL;
	ret->next = NULL;
	ret->redirections = NULL;
	return (ret);
}

t_red	*alloc_red_s(void)
{
	t_red	*ret;

	ret = malloc(sizeof(t_red));
	if (!ret)
		return (0);
	ret->arg = NULL;
	ret->next = NULL;
	ret->type = 0;
	return (ret);
}

int	sizeoftab(char	**tab)
{
	int	ret;

	ret = 0;
	while (tab[ret] != NULL)
		ret++;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:28:33 by zoizmer           #+#    #+#             */
/*   Updated: 2021/12/05 22:28:35 by zoizmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sizelen_norm(int *i, int *ret, char *str)
{
	int	trig;

	if (str[*i] == '\'')
	{
		*ret = *ret + 1;
		*i = *i + 1;
		trig = 1;
		while (str[*i])
		{
			if (str[*i] == '\'' && trig == 0)
				trig = 1;
			else if (str[*i] == '\'')
				trig = 0;
			if (str[*i] == ' ' && trig == 0)
				break ;
			*i = *i + 1;
		}
	}
	else if (str[*i] != ' ')
	{
		*ret = *ret + 1;
		while (str[*i] && str[*i] != ' ')
			*i = *i + 1;
	}
}

int	sizelen(char *str, int ret, int i, int trig)
{
	while (str[i])
	{
		if (str[i] == '"')
		{
			ret++;
			i++;
			trig = 1;
			while (str[i])
			{
				if (str[i] == '"' && trig == 0)
					trig = 1;
				else if (str[i] == '"')
					trig = 0;
				if (str[i] == ' ' && trig == 0)
					break ;
				i++;
			}
		}
		else if (str[i] != ' ' || str[i] == '\'')
			sizelen_norm(&i, &ret, str);
		if (str[i] == '"' || str[i] == '\'' || str[i] == ' ')
			i++;
	}
	return (ret);
}

char	*singlequote(char *str, int *s, int i)
{
	char	*ret;
	int		trig;

	trig = 1;
	while (str[*s + i])
	{
		if (str[*s + i] == '\'' && trig == 0)
			trig = 1;
		else if (str[*s + i] == '\'')
			trig = 0;
		if (str[*s + i] == ' ' && trig == 0)
			break ;
		*s = *s + 1;
	}
	ret = ft_substr(str + i, 0, *s);
	return (ret);
}

char	*doublequote(char *str, int *s, int i)
{
	char	*ret;
	int		trig;

	trig = 1;
	while (str[*s + i])
	{
		if (str[*s + i] == '"' && trig == 0)
			trig = 1;
		else if (str[*s + i] == '"')
			trig = 0;
		if (str[*s + i] == ' ' && trig == 0)
			break ;
		*s = *s + 1;
	}
	ret = ft_substr(str + i, 0, *s);
	return (ret);
}

char	*get_arg(char *str, int *r)
{
	int		i;
	char	*ret;
	int		s;

	i = *r;
	s = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\'')
		ret = singlequote(str, &s, i);
	else if (str[i] == '"')
		ret = doublequote(str, &s, i);
	else
	{
		while (str[s + i] && str[s + i] != ' ')
			s++;
		ret = ft_substr(str + i, 0, s);
	}
	*r = i + s;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:13:07 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 03:13:11 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_out_files(char type, char *arg)
{
	int	fd_out;

	if (type == 'o')
		fd_out = open(arg, O_CREAT | O_RDWR \
			| O_TRUNC, S_IWUSR | S_IRUSR);
	if (type == 'a')
		fd_out = open(arg, O_CREAT | O_RDWR \
			| O_APPEND, S_IWUSR | S_IRUSR);
	return (fd_out);
}

int	redirection_handler(t_cmd *strct)
{
	t_red	*tmp;
	int		fd_out;
	int		fd_in;

	tmp = strct->redirections;
	fd_in = -2;
	fd_out = -2;
	while (tmp != NULL)
	{
		fd_out = open_out_files(tmp->type, tmp->arg);
		if (tmp->type == 'i')
		{
			fd_in = open(tmp->arg, O_RDONLY | S_IRUSR);
			if (fd_in == -1)
				printf("%s :no such file or derictory\n", tmp->arg);
		}
		if (fd_in == -1 || fd_out == -1)
			exit(1);
		tmp = tmp->next;
	}
	if (fd_out != -1)
		dup2(fd_out, 1);
	if (fd_in != -1)
		dup2(fd_in, 0);
	return (0);
}

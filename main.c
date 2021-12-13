/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:28:52 by zoizmer           #+#    #+#             */
/*   Updated: 2021/12/05 22:28:54 by zoizmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write (1, "minishell>> ", 12);
		write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
		write (1, "  \b\b\n", 5);
		//rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	get_line(t_node *node,char **env/*i added this argument*/)
{
	char	*buf;

	buf = readline("minishell>> ");
	if (buf == NULL)
	{
		write(1, "exit\n", 5);
		free_node(node);
		exit(0);
	}
	if (ft_strlen(buf) > 0)
	{
		add_history(buf);
		if (scan(buf) == 0)
			write (1, "Minishell: Syntax error\n", 24);
		else
			parse_and_exec(buf, node,env/*i added this argument*/);
	}
	free(buf);
}

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	char	**newenv;
	int		i;

	node = NULL;
	i = 0;
	if (argc == 1)// i guess it should be if(argcc != 0)???
	{
		ft_strlen(argv[0]);
		newenv = copy_env(env);
		init_struct(newenv, &node);
		while (newenv[i++])
			free_null(newenv[i - 1]);
		free_null(newenv);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
		while (1)
			get_line(node,env/*i added this argument*/);
		return (0);
	}
	return (1);
}

char	*get_name(char	*str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

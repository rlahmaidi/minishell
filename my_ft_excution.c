/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ft_excution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:09:48 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 16:29:36 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_builtin_cmd(t_cmd *strct)
{
	if (!ft_strncmp(strct->cmd, "exit", 4) \
			|| !ft_strncmp(strct->cmd, "export", 6) \
			|| !ft_strncmp(strct->cmd, "env", 3) \
			|| !ft_strncmp(strct->cmd, "pwd", 3) \
			|| !ft_strncmp(strct->cmd, "cd", 2) \
			|| !ft_strncmp(strct->cmd, "unset", 5) \
			|| !ft_strncmp(strct->cmd, "echo", 4))
		return (0);
	else
		return (1);
}

void	builtins(t_cmd *strct, t_node *node)
{
	if (!ft_strcmp("cd", strct->args[0]))
		my_cd (strct->args, node);
	else if (!ft_strcmp("pwd", strct->args[0]))
		my_pwd (strct->args, node);
	else if (!ft_strcmp("env", strct->args[0]))
		my_env (strct->args, node);
	else if (!ft_strcmp("echo", strct->args[0]))
		my_echo (strct->args, node);
	else if (!ft_strcmp("exit", strct->args[0]))
		my_exit (strct->args, node);
	else if (!ft_strcmp("export", strct->args[0]))
		my_export (strct->args, node);
	else if (!ft_strcmp("unset", strct->args[0]))
		my_unset (strct->args, node);
}

char	*ft_get_path(char *bin, t_node *env)
{
	char		**bins;
	char		*path;
	int			i;
	struct stat	sb;

	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (ft_strdup(bin));
	bins = ft_split(env->val, ':');
	i = 0;
	while (bins[i])
	{
		path = ft_strjoin(bins[i], "/");
		path = ft_strjoin_free(path, bin);
		if (!stat(path, &sb))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int	ft_excution(t_cmd *strct, t_node *node)
{
	int			pid;
	int			fd[2];
	int			f;
	int			in;
	int			out;
	int			status;
	char		*path;
	char	*error_msg;

	f = -1;
	if (ft_strcmp(strct->args[0], "echo") == 0 \
			&& strct->args[1] && ft_strcmp(strct->args[1], "$?") == 0)
	{
		printf ("%d\n", g_ret);
		g_ret = 0;
		return (0);
	}
	if (!non_builtin_cmd(strct) && strct->next == NULL)
	{
		in = dup(0);
		out = dup(1);
		if (redirection_handler(strct) == -1)
			return (1);
		builtins(strct, node);
		dup2(in, 0);
		dup2(out, 1);
		return (0);
	}
	while (strct != NULL)
	{
		if (pipe(fd) < 0)
			return (1);
		if ((pid = fork()) < 0)
			return (1);
		else if (pid == 0)
		{
			if (strct->next != NULL)
			{
				dup2(fd[1], 1);
				close(fd[1]);//why
				close(fd[0]);
			}
			if (f != -1)
			{
				dup2(f, 0);
				close(f);
			}
			if (redirection_handler(strct) == -1)
				exit(1);
			if (non_builtin_cmd(strct))
			{
				path = ft_get_path(strct->args[0], node);
				if (path == NULL)
				{
					write(2, "minishell: ", ft_strlen("minishell: "));
					write(2, strct->args[0], ft_strlen(strct->args[0]));
					write(2, ": command not found\n", ft_strlen(": command not found") + 1);
					exit (127);
				}
				execve(path, strct->args, list_to_env(node));
				error_msg = strerror(errno);
				write(2, "minishell: ", ft_strlen("minishell: "));
				write(2, error_msg, ft_strlen(error_msg));
				write(2, "\n", 1);
				if (errno == 2)
					exit(127);
				else if (errno == 13 || errno == 21)
					exit(126);
			}
			else
			{
				builtins(strct, node);
				close(fd[1]);
				exit(1);
			}
			exit(0);
		}
		close(fd[1]);
		if (f != -1)
			close(f);
		f = fd[0];
		strct = strct->next;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status) == true)
		g_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status) == true)
		g_ret = 128 + WTERMSIG(status);
	return (0);
}

// while(cmd)
// {
// 	int fd[2];
// 	int f = -1;
// 	pipe(fd);
// 	fork;
// 	if(pid == 0)
// 	{
// 		if(ila makanch how akhir comd)               // mastapha;
// 			dup2(fd[1],1);
// 		if (f != -1)
// 			dup2(f, 0);
// 		close(fd[0]);
// 		exuction;
// 	}
// 	else
// 	{
// 	f = fd[0];
// 	close(fd[1]);
// 	}
// }

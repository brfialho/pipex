/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:43:59 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/13 18:54:27 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	first_child(t_pipex *pipex, char **args);
static void	last_child(t_pipex *pipex, char **args);

void	create_childs(t_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
		destroy_all(pipex, PIPE);
	if (!fork())
		first_child(pipex, ((t_list *)*pipex->cmd)->content);
	if (!fork())
		last_child(pipex, ((t_list *)*pipex->cmd)->next->content);
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
}

void	kill_childs(t_pipex *pipex)
{
	int	childs;

	childs = lst_size(*pipex->cmd);
	while (childs--)
		waitpid(0, NULL, 0);
}

static void	first_child(t_pipex *pipex, char **args)
{
	char	*bin;

	bin = ft_strjoin("/bin/", args[0]);
	if (!bin)
		destroy_all(pipex, MEM);
	close(pipex->pipe[READ]);
	dup2(pipex->input.fd, 0);
	close(pipex->input.fd);
	dup2(pipex->pipe[WRITE], 1);
	close(pipex->pipe[WRITE]);
	execv(bin, args);
	ft_printf("Command '%s' not found\n", args[0]);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}

static void	last_child(t_pipex *pipex, char **args)
{
	char	*bin;

	bin = ft_strjoin("/bin/", args[0]);
	if (!bin)
		destroy_all(pipex, MEM);
	close(pipex->pipe[WRITE]);
	dup2(pipex->pipe[READ], 0);
	close(pipex->pipe[READ]);
	dup2(pipex->output.fd, 1);
	close(pipex->output.fd);
	execv(bin, args);
	ft_printf("Command '%s' not found\n", args[0]);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}

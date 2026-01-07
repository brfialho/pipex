/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:05:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/07 20:42:48 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parse_cmd_lst(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	pipex->cmd = ft_calloc(1, sizeof(t_list **));
	if (!pipex->cmd)
		exit(2);
	i = 1;
	while (++i < argc - 1)
		lst_add_end(pipex->cmd, lst_new_node(argv[i]));
}


void	parsing(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
		exit(1);
	parse_cmd_lst(pipex, argc, argv);
	pipex->input.path = argv[1];
	pipex->output.path = argv[argc - 1];
}
void	print_node(void *content)
{
	ft_printf("%s\n", (char *)content);
}

int	main(int argc, char **argv)
{
	t_pipex	pipex;

	parsing(&pipex, argc, argv);
	lst_for_each(*pipex.cmd, print_node);
	lst_del_all(pipex.cmd, NULL);
	free(pipex.cmd);
}

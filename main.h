/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:07:45 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/10 14:37:24 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_file
{
	char	*path;
	int		fd;
}	t_file;

typedef struct s_pipex
{
	int		pid;
	int		pipe[2];
	t_file	input;
	t_file	output;
	t_list	**cmd;
}	t_pipex;

typedef enum e_error
{
	CLEAN,
	INPUT_FILE,
	OPEN,
	MEM
}	t_error;

#endif
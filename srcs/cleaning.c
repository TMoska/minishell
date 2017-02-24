/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:11:46 by moska             #+#    #+#             */
/*   Updated: 2017/02/24 17:38:59 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_list(void **a, size_t *b)
{
	(void)b;
	ft_strdel((char**)a);
}

void	mid_clean_shell(t_shell **shell)
{
	(void)shell;
	ft_lstdel(&(*shell)->commands, clean_list);
	ft_strdel(&((*shell)->buff));
}

void	clean_shell(t_shell **shell)
{
	ft_str2del(&(*shell)->env);
	clean_env_list(&(*shell)->env_list);
}

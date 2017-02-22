/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:53:21 by moska             #+#    #+#             */
/*   Updated: 2017/02/21 20:55:54 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void rebuild_str2env(t_shell **shell)
{
  t_envl  *tmp;
  char    **new;
  int     i;

  i = 0;
  tmp = (*shell)->env_list;
  new = ft_str2new(env_lst_size(tmp));
  while (tmp)
  {
    new[i] = ft_str3join(tmp->name, "=", tmp->value);
    tmp = tmp->next;
    i++;
  }
  ft_str2del(&(*shell)->env);
  (*shell)->env = new;
}
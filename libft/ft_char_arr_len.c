/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_arr_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 02:46:40 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 16:04:29 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_char_arr_len(char **arr)
{
	int i;

	i = 0;
	while (*arr)
	{
		i++;
		arr++;
	}
	return (i);
}

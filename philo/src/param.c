/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:23:55 by swautele          #+#    #+#             */
/*   Updated: 2022/04/04 12:17:09 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

t_param	*init_param(int argc, char **argv)
{
	t_param	*set;
	char	flagerr;

	set = malloc(sizeof(t_param));
	flagerr = 0;
	set->number = ft_atoi(argv[1], &flagerr);
	set->death = ft_atoi(argv[2], &flagerr);
	set->eat = ft_atoi(argv[3], &flagerr);
	set->sleep = ft_atoi(argv[4], &flagerr);
	if (argc == 6)
		set->meal = ft_atoi(argv[5], &flagerr);
	else
		set->meal = -1;
	if (flagerr == -1)
		set->number = -1;
	if (flagerr == -1)
	{
		free (set);
		return (NULL);
	}
	return (set);
}

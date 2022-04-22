/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:23:55 by swautele          #+#    #+#             */
/*   Updated: 2022/04/22 18:36:08 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

t_param	*init_param(int argc, char **argv)
{
	t_param	*set;
	char	flagerr;

	set = malloc(sizeof(t_param));
	if (set == NULL)
		return (NULL);
	memset(set, 0, sizeof(t_param));
	flagerr = 0;
	set->number = ft_atoi(argv[1], &flagerr);
	set->death = ft_atoi(argv[2], &flagerr);
	set->eat = ft_atoi(argv[3], &flagerr);
	set->sleep = ft_atoi(argv[4], &flagerr);
	if (argc == 6)
		set->meal = ft_atoi(argv[5], &flagerr);
	else
		set->meal = -1;
	if (flagerr == -1 || set->number <= 0 || set->death < 0 || set->eat < 0
		|| set->sleep < 0 || (argc == 6 && set->meal < 0) || set->number > 200)
	{
		free (set);
		return (NULL);
	}
	return (set);
}

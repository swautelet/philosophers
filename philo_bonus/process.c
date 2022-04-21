/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/21 16:47:05 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo(t_param *param, t_param *info, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < param->number)
	{
		*(info + i) = *param;
		(info + i)->pos = i + 1;
		if (i > 0)
			(info + i)->lfork = fork + i - 1;
		else
			(info + i)->lfork = fork + param->number - 1;
		(info + i)->rfork = fork + i;
		pthread_mutex_init(fork + i, NULL);
	}
}

static void	threadinator(pthread_t *philo, t_param *info, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < info->number)
	{
		pthread_create(philo + i, NULL, &philo_routine, info + i);
	}
	i = -1;
	while (++i < info->number)
		pthread_join(*(philo + i), NULL);
	i = -1;
	while (++i < info->number)
		pthread_mutex_destroy(fork + i);
}

int	create_process(t_param *param)
{
	param->forks = malloc(sizeof(sem_t));
	param->speachrod = malloc(sizeof(pthread_mutex_t));
	if (param->speachrod == NULL || param->forks == NULL)
		return (-1);
	pthread_mutex_init(param->speachrod, NULL);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	param->lastmeal.tv_sec++;
	init_philo(param, param, fork);
	threadinator(param, param, fork);
	free (param->speachrod);
	free (param->forks);
	return (0);
}

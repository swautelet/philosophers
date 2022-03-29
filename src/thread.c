/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/03/29 16:46:14 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_param param, struct timeval start)
{
	int				i;
	pthread_mutex_t	*fork;
	pthread_t		*philo;
	t_param			*info;

	(void)start;
	fork = malloc(sizeof(pthread_mutex_t) * param.number);
	philo = malloc(sizeof(pthread_t) * param.number);
	info = malloc(sizeof(t_param) * param.number);
	i = -1;
	while (++i < param.number)
	{
		*(info + i) = param;
		(info + i)->pos = i;
		pthread_mutex_init(fork + i, NULL);
		pthread_create(philo + i, NULL, &philo_routine, info + i);
	}
	i = -1;
	while (++i < param.number)
		pthread_join(*(philo + i), NULL);
	i = -1;
	while (++i < param.number)
		pthread_mutex_destroy(fork + i);
	free (fork);
	free (philo);
	free (info);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/22 13:23:02 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	init_philo(t_param *param, t_param *info, pthread_mutex_t *fork)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < param->number)
// 	{
// 		*(info + i) = *param;
// 		(info + i)->pos = i + 1;
// 		if (i > 0)
// 			(info + i)->lfork = fork + i - 1;
// 		else
// 			(info + i)->lfork = fork + param->number - 1;
// 		(info + i)->rfork = fork + i;
// 		pthread_mutex_init(fork + i, NULL);
// 	}
// }

static void	processinator(t_param *data)
{
	int	i;
	int	id;

	i = 0;
	while (++i <= data->number)
	{
		id = fork();
		if (id != 0)
		{
			data->pos = i;
			philo_routine(data);
			exit(0) ;
		}
	}
	i = -1;
	while (++i < data->number)
		waitpid(-1, &id, P_ALL);
	if (sem_close(data->forks) == -1)
		if (sem_unlink("forks") == -1)
			usleep(1);
			// free (data->forks);
	// sem_unlink("forks");
}

int	create_process(t_param *param)
{
	// int	test;

	param->forks = malloc(sizeof(sem_t));
	if (param->forks == NULL)
		return (-1);
	param->speachrod = malloc(sizeof(pthread_mutex_t));
	if (param->speachrod == NULL)
	{
		free (param->forks);
		return (-1);
	}
	pthread_mutex_init(param->speachrod, NULL);
	param->forks = sem_open("forks", O_CREAT, O_RDWR, param->number);
	// sem_getvalue(param->forks, &test);
	// printf("semvalue = %d", test);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	// init_philo(param, param, fork);
	processinator(param);
	// printf("speachrod  = %p		forks = %p", param->speachrod, param->forks);
	free (param->speachrod);
	// free (param->forks);
	return (0);
}

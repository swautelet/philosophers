/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/22 18:29:09 by swautele         ###   ########.fr       */
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
	int	ret;
	int	id[200];

	memset(id, 0, sizeof(int) * 200);
	i = -1;
	while (++i <= data->number)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			data->pos = i;
			philo_routine(data);
			exit(0) ;
		}
	}
	ret = 0;
	while ((i = waitpid(-1, &ret, WNOHANG)) >= 0)
	{
        if (i > 0)
		{
			i = -1;
			while(id[++i] != 0)
				kill(id[i], SIGINT);
			sem_post(data->speachrod);
		}
	}	
	// while (waitpid(-1, &ret, WNOHANG) != -1)
		// usleep(1000);
	// usleep(1000);
	// printf("test\n");
	sem_close(data->forks);
	sem_close(data->speachrod);
	// sem_unlink("/forks");
	// if (sem_close(data->forks) == -1)
		// if (sem_unlink("/forks") == -1)
			// usleep(1);
			// free (data->forks);
	// sem_unlink("forks");
}

int	create_process(t_param *param)
{
	// int	test;

	// param->forks = malloc(sizeof(sem_t));
	// if (param->forks == NULL)
		// return (-1);
	// param->speachrod = malloc(sizeof(sem_t));
	// if (param->speachrod == NULL)
	// {
		// free (param->forks);
		// return (-1);
	// }
	sem_unlink("/forks");
	sem_unlink("/speach");
	param->speachrod = sem_open("/speach", O_CREAT, S_IRUSR | S_IWUSR, 1);
	// pthread_mutex_init(param->speachrod, USYNC_PROCESS);
	param->forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, param->number);
	// sem_init(param->forks, 1, param->number);
	// sem_getvalue(param->forks, &test);
	// printf("semvalue = %d\n", test);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	// init_philo(param, param, fork);
	processinator(param);
	// printf("speachrod  = %p		forks = %p", param->speachrod, param->forks);
	// free (param->speachrod);
	// free (param->forks);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:12:43 by swautele          #+#    #+#             */
/*   Updated: 2022/03/29 17:22:56 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_param{
	int				number;
	int				death;
	int				eat;
	int				sleep;
	int				meal;
	int				pos;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct timeval	start;
}	t_param;

int		ft_atoi(const char *str, char *flagerr);
int		create_thread(t_param param);
t_param	init_param(int argc, char **argv);
void	*philo_routine(void *info);

#endif

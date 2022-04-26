# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 14:48:19 by swautele          #+#    #+#              #
#    Updated: 2022/04/26 13:07:06 by simonwautel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FILES = src/philosophers.c \
	src/param.c \
	src/thread.c \
	src/ft_atoi.c \
	src/routine.c \
	src/time.c
CC = gcc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=thread
OBJECT = $(FILES:.c=.o)

all : $(NAME)

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

.o : .c
	$(CC) $(CFLAGS) $? -o $@

test : re
	./$(NAME) 200 130 60 60 20

re : fclean all

bonus :
	make -C ../philo_bonus

save :
	git commit -am autosave
	git push https://github.com/swautelet/philosophers.git

.phony : save test fclean clean
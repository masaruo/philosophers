# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2023/07/20 14:10:11 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror
FILES		=	main threads utils finalize ft_atoi ft_atoi_utils init\
				ft_calloc monitor
FILES_BONUS	=	main_bonus ft_atoi_bonus ft_atoi_utils_bonus ft_calloc_bonus\
				utils_bonus process_bonus init_bonus
SRCS_DIR	=	./srcs/
BSRCS_DIR	=	./srcs_bonus/
SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
BSRCS		=	$(addprefix $(BSRCS_DIR), $(addsuffix .c, $(FILES_BONUS)))
INC			=	./includes/
OBJS		=	$(SRCS:.c=.o)
BOBJS		=	$(BSRCS:.c=.o)

ifdef DEBUG
CFLAGS	=	-Wall -g3 -O0 -fsanitize=address
endif

ifdef DEV
CFLAGS	=	-Wall -g3 -O0 -fsanitize=thread -fno-omit-frame-pointer
endif

%.o : %.c
	$(CC) $(CFLAGS) -I $(INC) -c -o $@ $<

all: $(NAME)

bonus: $(NAME)_bonus

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


$(NAME)_bonus: $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) -o $@

	
clean:
	$(RM) $(OBJS)
	$(RM) $(BOBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)_bonus

re: fclean all

debug: fclean
	make $(NAME) DEBUG=1

dev: fclean
	make $(NAME) DEV=1

.PHONY: debug dev all clean fclean re

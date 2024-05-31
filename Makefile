# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jason <jason@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 18:18:13 by mkhaing           #+#    #+#              #
#    Updated: 2024/05/31 22:20:47 by jason            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                       _oo0oo_
#                      o8888888o
#                      88" . "88
#                      (| -_- |)
#                      0\  =  /0
#                    ___/`---'\___
#                  .' \\|     |// '.
#                 / \\|||  :  |||// \
#                / _||||| -:- |||||- \
#               |   | \\\  -  /// |   |
#               | \_|  ''\---/''  |_/ |
#               \  .-\__  '-'  ___/-. /
#             ___'. .'  /--.--\  `. .'___
#          ."" '<  `.___\_<|>_/___.' >' "".
#         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
#         \  \ `_.   \_ __\ /__ _/   .-` /  /
#     =====`-.____`.___ \_____/___.-`___.-'=====
#                       `=---='
#
#
#     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#               佛祖保佑         永无BUG
#

NAME    = bjsh

SRC_DIR = src/
BYAMC_D =./byamc

BYAMC   = $(BYAMC_D)/byamc.a

CC      = gcc #clang

#CFLAGS  = -Wall -Wextra -Werror -D LINUX #-fsanitize=leak -g
CFLAGS	= -DSHELL_BUILD_DATE="\"`date`\"" -Ibyamc/include -Iinclude -lreadline -lhistory 

RM      = rm -f

MINISHELL_SRC = $(wildcard $(SRC_DIR)bjsh/*.c)	\
				$(wildcard $(SRC_DIR)token_handler/*.c)	\
				$(wildcard $(SRC_DIR)utils/*.c)

SRCS        =   $(MINISHELL_SRC)

OBJS        =   ${SRCS:.c=.o}

all:			$(BYAMC) $(NAME)        

$(NAME):		$(OBJS) $(BYAMC)
				$(CC) $(CFLAGS) $(OBJS) $(BYAMC) -o $(NAME)

$(BYAMC):
				make -C $(BYAMC_D) all

clean:
				${RM} ${OBJS}
				make -C $(BYAMC_D) clean

format:
				c_formatter_42 ./include/*.h
				c_formatter_42 ./src/bjsh/*.c

install:
				sudo cp ./bjsh /bin/bjsh --force

fclean:         clean
				${RM} ${BYAMC}
				${RM} ${NAME}

re:             fclean all

.PHONY:         all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 18:18:13 by mkhaing           #+#    #+#              #
#    Updated: 2024/06/17 16:46:30 by mkhaing          ###   ########.fr        #
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
CFLAGS	= -g -DSHELL_BUILD_DATE="\"`date`\"" -Ibyamc/include -Iinclude
LDFLAGS = -L/lib/x86_64-linux-gnu -lreadline -lhistory     # Ubuntu is so dumb need -L flag to find readline
RM      = rm -f

MINISHELL_SRC = $(wildcard $(SRC_DIR)bjsh/*.c)	\
				$(wildcard $(SRC_DIR)evaluator/*.c) \
				$(wildcard $(SRC_DIR)helper/*.c) 

SRCS        =   $(MINISHELL_SRC)

OBJS        =   ${SRCS:.c=.o}

all:			$(BYAMC) $(NAME)        

$(NAME):		$(OBJS) $(BYAMC)
				$(CC) $(CFLAGS) $(OBJS) $(BYAMC) $(LDFLAGS) -o $(NAME)

$(BYAMC):
				make -C $(BYAMC_D) all

clean:
				${RM} ${OBJS}
				make -C $(BYAMC_D) clean

format:
				c_formatter_42 ./include/*.h
				c_formatter_42 ./src/bjsh/*.c
				c_formatter_42 ./src/evaluator/*.c

install:
				sudo cp ./bjsh /bin/bjsh --force

fclean:         clean
				${RM} ${BYAMC}
				${RM} ${NAME}

re:             fclean all

.PHONY:         all clean fclean re

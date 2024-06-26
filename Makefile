# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 18:18:13 by mkhaing           #+#    #+#              #
#    Updated: 2024/06/27 00:43:12 by mkhaing          ###   ########.fr        #
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

CC      = gcc #gcc

# Get the Git commit hash using the $(shell) function
GIT_COMMIT := $(shell git describe --always --dirty --match 'NOT A TAG')

#CFLAGS  =  #-fsanitize=leak -g
CFLAGS	= -g -Wall -Wunused-function -Wextra -Werror -D LINUX -fPIE -fstack-protector-strong -DGIT_COMMIT=\"$(GIT_COMMIT)\" -DSHELL_BUILD_DATE="\"`date`\"" -Ibyamc/include -Iinclude
LDFLAGS = -L/lib/x86_64-linux-gnu -lreadline -lhistory     # Ubuntu is so dumb need -L flag to find readline
RM      = rm -f

MINISHELL_SRC = $(wildcard $(SRC_DIR)bjsh/*.c)	\
				$(wildcard $(SRC_DIR)builtins/*.c) \
				$(wildcard $(SRC_DIR)evaluator/*.c) \
				$(wildcard $(SRC_DIR)execution/*.c) \
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

check-unused:
				cppcheck  --enable=unusedFunction --check-level=exhaustive --enable=all --std=c99 -Iinclude src	

check-leaks:
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.readline.supp ./$(NAME)

install:
				sudo cp ./bjsh /bin/bjsh --force

fclean:         clean
				${RM} ${BYAMC}
				${RM} ${NAME}

me:				re

re:             fclean all

.PHONY:         all clean fclean re

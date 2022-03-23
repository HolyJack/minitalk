# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 16:45:53 by ejafer            #+#    #+#              #
#    Updated: 2022/03/23 13:11:26 by ejafer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME1		= server
NAME2		= client

HDR_DIR		= include/
SRC_DIR		= src/
OBJ_DIR		= obj/

HDR			= minitalk.h


SRC1_NAMES	= mt_server utils_server
SRC2_NAMES	= mt_client utils_client

SRC1		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC1_NAMES)))
OBJ1		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC1_NAMES)))
D1_FILES	= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC1_NAMES)))

SRC2		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC2_NAMES)))
OBJ2		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC2_NAMES)))
D2_FILES	= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC2_NAMES)))


CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3

MD			= mkdir -p

all: ${NAME1} ${NAME2}

$(NAME1): ${OBJ1} Makefile
	${CC} ${CFLAGS} ${OBJ1} -o ${NAME1}

$(NAME2): ${OBJ2} Makefile
	${CC} ${CFLAGS} ${OBJ2} -o ${NAME2}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@${MD} ${OBJ_DIR}
	$(CC) $(CFLAGS) -I${HDR_DIR} -c $< -o $@ -MD

include $(wildcard $(D1_FILES))
include $(wildcard $(D2_FILES))

clean:
	${RM} ${OBJ1} ${OBJ2} ${D1_FILES} ${D2_FILES}

fclean: clean
	${RM} ${NAME1} ${NAME2}

re: clean fclean all

.PHONY: re clean fclean all
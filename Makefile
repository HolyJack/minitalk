# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 16:45:53 by ejafer            #+#    #+#              #
#    Updated: 2022/03/23 16:05:22 by ejafer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME1		= server
NAME2		= client

HDR_DIR		= include/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR   = libft/

HDR			= minitalk.h
LIBFT		= libft/libft.a

SRC1_NAMES	= mt_server
SRC2_NAMES	= mt_client

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

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(NAME1): ${OBJ1} Makefile | $(LIBFT)
		${CC} ${CFLAGS} ${OBJ1} -L$(LIBFT_DIR) -lft -o ${NAME1}

$(NAME2): ${OBJ2} Makefile | $(LIBFT)
		${CC} ${CFLAGS} ${OBJ2} -L$(LIBFT_DIR) -lft -o ${NAME2}

$(OBJ_DIR):
		${MD} ${OBJ_DIR}

${OBJ_DIR}%.o: ${SRC_DIR}%.c | ${OBJ_DIR}
		$(CC) $(CFLAGS) -I${HDR_DIR} -c $< -o $@ -MD

include $(wildcard $(D1_FILES))
include $(wildcard $(D2_FILES))

clean:
	$(MAKE) -C $(LIBFT_DIR) $(MAKECMDGOALS)
	${RM} ${OBJ1} ${OBJ2} ${D1_FILES} ${D2_FILES}

fclean: clean
	${RM} ${NAME1} ${NAME2}

re: clean fclean all

.PHONY: re clean fclean all
#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2016/06/09 11:28:58 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	lem-in

C_SRC =		main.c		error.c
C_PARSER =	parse.c		
C_DOER =	

O_DIR = obj
C_DIR = src
VPATH =	src:src/parser:src/doer

SRCC = 	$(C_SRC:%.c=src/%.c)		$(C_PARSER:%.c=src/parser/%.c)	\
		$(C_DOER:%.c=src/doer/%.c) 
OBJS =	$(C_SRC:%.c=$(O_DIR)/%.o)	$(C_PARSER:%.c=$(O_DIR)/%.o)	\
		$(C_DOER:%.c=$(O_DIR)/%.o)
DEPS =  $(OBJS:%.o=%.d)

LIB =
LIBFT =		libft/libft.a
I_DIR =		-I./libft/inc/ -I./inc/
MAKE =		make -j
RM =		rm -rf
MKDIR =		mkdir -p
CC =		clang
CFLAGS =	-Wall -Wextra -Werror

WHITE =	\033[37;01m
RED =	\033[31;01m
GREEN =	\033[32;01m
BLUE =	\033[34;01m
BASIC =	\033[0m

.PHONY: all debug sanitize me_cry clean fclean zclean re brute

all:
	@$(MAKE) -C libft
	@$(MAKE) $(NAME)

debug:
	@$(MAKE) -C libft debug
	@$(MAKE) $(NAME) "CFLAGS = -g -ggdb"

sanitize:
	@$(MAKE) -C libft sanitize
	@$(MAKE) $(NAME) \
		"CFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"

me_cry:
	@$(MAKE) -C libft
	@$(MAKE) $(NAME) \
		"CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual

-include $(DEPS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(I_DIR) $(OBJS) $(LIBFT) -o $@ $(LIB)
	@echo "$(BLUE)$(OBJS) $(WHITE)->$(RED) $@ $(BASIC)"
	@echo "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@echo "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@
	@echo "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"

$(OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@make -C libft fclean

re: fclean all

brute: zclean all

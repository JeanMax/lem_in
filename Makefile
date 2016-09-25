#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2016/09/25 18:58:40 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	lem-in

C_SRC =		error.c		lemin_main.c
C_PARSER =	parse.c		room.c
C_DOER =	do.c

O_DIR = obj
VPATH =	src:src/parser:src/doer

OBJS =		$(C_PARSER:%.c=$(O_DIR)/%.o)	$(C_DOER:%.c=$(O_DIR)/%.o) \
			$(C_SRC:%.c=$(O_DIR)/%.o)
DEPS =		$(OBJS:%.o=%.d)

MAKE =		make -j
RM =		rm -rf
MKDIR =		mkdir -p
CC =		clang
CFLAGS =	-Wall -Wextra -Werror -O2
LIBFT_DIR =	libft
LIBFT	 =	$(LIBFT_DIR)/libft.a
N_LIBS = 	$(LIBFT) #-L$(LIBFT_DIR) -lft
I_DIR =	-Iinc/ -I$(LIBFT_DIR)/inc/

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

.PHONY: all debug sanitize me_cry clean fclean zclean re brute

all:
	@$(MAKE) -C $(LIBFT_DIR) $(FLAGS)
	@$(MAKE) $(NAME) $(FLAGS)

debug: FLAGS = "CFLAGS = -g -ggdb"
debug: all

sanitize: FLAGS = "CFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"
sanitize: all

me_cry: FLAGS = "CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual
me_cry: all

-include $(DEPS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(I_DIR) $(OBJS) $(N_LIBS) -o $@
	@echo "$(BLUE)$(OBJS) $(N_LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	@echo "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@echo "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@
	@echo "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"

$(OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)
	@echo "$(O_DIR)" > .gitignore
	@echo "$(NAME)" >> .gitignore
	@echo "$(VISU)" >> .gitignore

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

brute: zclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 06:01:21 by nsainton          #+#    #+#              #
#    Updated: 2023/07/28 14:23:05 by nsainton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libgc.a

SRCS_DIR= sources

SRCS_SUBDIRS:= $(shell find $(SRCS_DIR) -type d)

SRCS_NAMES:= gc_alloc.c gc_array.c gc_del.c gc_helpers.c gc_management.c \
			gc_structure.c t_tab/allocation.c t_tab/management.c t_str/t_str.c \
			t_list/lst_add.c t_list/lst_free.c wrappers/itoa.c wrappers/split.c \
			wrappers/strs.c

SRCS= $(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))

OBJS_DIR= objects

OBJS_NAMES= $(SRCS_NAMES:.c=.o)

OBJS= $(addprefix $(OBJS_DIR)/, $(OBJS_NAMES))

DEPS_DIR := dependancies

DEPS_NAME := $(patsubst %.c, $(DEPS_DIR)/%.d, $(SRCS_NAMES))

INC_DIR= includes

CC= cc

CFLAGS= -Wall -Wextra -Werror

AR= ar -rc

MK:= mkdir -p

LIBS := libs

LIBS_DIR ?= $(shell pwd)/libs

LFT_DIR := $(LIBS_DIR)/libft

LFT_URL := git@github.com:nsainton/libft.git

LFT := $(LFT_DIR)/libft.a

export LIBS_DIR
export C_INCLUDE_PATH=$(INC_DIR):$(LFT_DIR)/$(INC_DIR)

#Color codes for pretty printing
BEGIN=\033[
BLACK=30
RED=31
GREEN=32
BROWN=33
BLUE=34
PURPLE=35
CYAN=36
NORMAL=0
BOLD=1
UNDERLINED=4
BLINKING=5
REVERSE=7
END=\033[0m

#Here is the definition of an ascii code
#double backslash at the end of lines to ensure that it is not interpreted
#as line continuation. One could also have added a space after the backslash
#The export directive makes the header available to each submake
#Font used is Sub-Zero
define libgc_header
 __         __     ______     ______    
/\ \       /\ \   /\  ___\   /\  ___\   
\ \ \____  \ \ \  \ \ \__ \  \ \ \____  
 \ \_____\  \ \_\  \ \_____\  \ \_____\ 
  \/_____/   \/_/   \/_____/   \/_____/ 

endef
export libgc_header

define compiled_header
  ______  ______  __    __  ______  __  __      ______  _____    
 /\  ___\/\  __ \/\ "-./  \/\  == \/\ \/\ \    /\  ___\/\  __-.  
 \ \ \___\ \ \/\ \ \ \-./\ \ \  _-/\ \ \ \ \___\ \  __\\ \ \/\ \ 
  \ \_____\ \_____\ \_\ \ \_\ \_\   \ \_\ \_____\ \_____\ \____- 
   \/_____/\/_____/\/_/  \/_/\/_/    \/_/\/_____/\/_____/\/____/ 
endef
export compiled_header

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	echo "$(BEGIN)$(GREEN)m"
	echo "$$libgc_header"
	echo "$$compiled_header"
	echo "$(END)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(LFT_DIR)
	[ -d $(@D) ] || $(MK) $(@D)
	arg="$$(dirname $(DEPS_DIR)/$*)"; \
	[ -d $$arg ] || $(MK) $$arg
	$(CC) $(CFLAGS) $(GG) $(OPT) -MD -MF $(DEPS_DIR)/$*.d -c $< -o $@

$(DEPS_DIR):
	$(MK) $(DEPS_DIR)

$(LFT_DIR):
	git clone $(LFT_URL) $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

debug:
	make re GG=-g3 OPT=-O0 CC=gcc

clean:
	rm -rf $(OBJS_DIR)
	echo "$(BEGIN)$(RED)mObjects have been successfully removed$(END)"

oclean:
	rm -f $(NAME)
	echo "$(BEGIN)$(RED);$(UNDERLINED)m$(NAME)\
	$(BEGIN)$(NORMAL);$(CYAN)m has been successfully removed$(END)"

lclean:
	$(RM) -r $(LIBS_DIR)
	echo "$(BEGIN)$(PURPLE)m libraries have been successfully removed$(END)"
fclean:
	$(MAKE) clean
	$(MAKE) oclean

re: fclean all

git:
	git add --all
	git commit
	git push origin dev

maketest:
	echo $(LIBS_DIR)
	echo $(SRCS_NAMES)

.PHONY: all debug clean fclean re git
.SILENT:

-include $(DEPS)

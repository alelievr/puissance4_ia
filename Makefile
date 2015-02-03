# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdaudre- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/07/15 15:13:38 by fdaudre-          #+#    #+#              #
#    Updated: 2015/02/03 17:27:05 by fdaudre-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Auteur: fdaudre-

#################
##  VARIABLES  ##
#################

#	Sources
SRCDIR		=	src
SRC			=	main_dev.c				\
				p4_getmove_fperruch.c	\
				p4_tool.c				\
				p4_won.c			#	\
				calc_score.c

#	Objects
OBJDIR		=	obj

#	Includes
INCDIR		=	.

#	Libraries
LIBDIR		=	
LIB			=	

#	Output
NAME		=	p4

#	Compiler
CFLAGS		=	-O3 -Werror -Wall -Wextra
CC			=	clang


#################
##  AUTO       ##
#################

SHELL		=	/bin/zsh
OBJ			=	$(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFLAG		=	$(addprefix -L,$(LIBDIR))
INCFLAG		=	$(addprefix -I,$(INCDIR))
NORME		=	$(addsuffix /*.h,$(INCDIR)) $(addprefix $(SRCDIR)/,$(SRC))

$(foreach S,$(SRC), \
	$(eval VPATH += $(SRCDIR)/$(dir $(S)) \
	) \
)

disp_indent	=	for I in `seq 1 $(MAKELEVEL)`; do \
					test "$(MAKELEVEL)" '!=' '0' && printf "\t"; \
				done

exec_color	=	$(call disp_indent); \
			echo $(1)$(2) $(3) $(4) $(5) $(6) $(7) $(8) $(9) $(10)"\033[31m"; \
			$(2) $(3) $(4) $(5) $(6) $(7) $(8) $(9) $(10)

disp_title	=	$(call disp_indent); \
				echo "\033[1;$(2);7m[  $(1) \#$(MAKELEVEL)  ]\033[0m"


#################
##  TARGETS    ##
#################

#	First target
all: $(NAME)

#	Linking
$(NAME): $(OBJ)
	@$(call disp_title,Linking,32);
	@$(call exec_color,"\033[0;1;32m➤ \033[0;38;5;85m",\
		$(CC), $(LIBFLAG), -o, $(NAME), $(LIB), $(OBJ)) # <- Linking command

#	Objects compilation
$(OBJDIR)/%.o: %.c
	@if [ $(ALREADY_OBJ)x != xx ]; then \
		$(call disp_title,Building,36); \
	fi
	@mkdir $(OBJDIR) 2> /dev/null || echo "" > /dev/null
	@$(call exec_color,"\033[0;1;36m➤ \033[0;38;5;159m",\
		$(CC), $(CFLAGS), $(INCFLAG), -o, $@, -c, $<) # <- Building command
	@$(eval ALREADY_OBJ=x)

#	Removing objects
clean:
	@if [ $(ALREADY_RM)x != xx ]; then \
		$(call disp_title,Cleaning,33); \
	fi
	@$(call exec_color,"\033[0;1;33m➤ \033[0;38;5;229m",\
		rm -f, $(OBJ)) # <- Cleaning objs
	@rmdir $(OBJDIR) 2> /dev/null || echo "" > /dev/null
	@$(eval ALREADY_RM=x)

#	Removing objects and exe
fclean: clean
	@if [ $(ALREADY_RM)x != xx ]; then \
		$(call disp_title,Cleaning,33); \
	fi
	@$(call exec_color,"\033[0;1;33m➤ \033[0;38;5;229m",\
		rm -f, $(NAME)) # <- Cleaning binary
	@$(eval ALREADY_RM=x)

#	All removing then compiling
re: fclean all

#	Checking norme
norme:
	@$(call disp_title,Norme,37)
	@norminette $(NORME) | sed "s/Norme/[0;1;37m➤ [0;38;5;254mNorme/g;s/Warning/[0;31mWarning/g;s/Error/[0;31mError/g"

run: $(NAME)
	@echo "\033[1;35;7m[  Running #$(MAKELEVEL)  ]\033[0m"
	@echo "\033[0;1;35m➤ \033[0;38;5;147m./$(NAME) ${ARGS}\033[0m"
	@./$(NAME) ${ARGS}

codesize:
	@cat $(NORME) |grep -v '/\*' |wc -l

.PHONY: all clean fclean re norme codesize

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 16:30:35 by Nathanael         #+#    #+#              #
#    Updated: 2022/07/14 18:28:52 by Nathanael        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

################################################################################
#								DIRECTORIES									   #
################################################################################
BUILDIR	=	./build
HDRDIR	=	./headers
LIBDIR	=	./libraries
SRCDIR	=	./sources
IDRDIR	=	./headers/imported

TEMPDIR =	$(BUILDIR) $(IDRDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	\
$(SRCDIR)/execute.c \
$(SRCDIR)/main.c \
$(SRCDIR)/command_list.c \
$(SRCDIR)/redir/here_doc.c \
$(SRCDIR)/redir/remove_redir.c \
$(SRCDIR)/redir/std_sort.c \
$(SRCDIR)/redir/std_io.c \
$(SRCDIR)/utils/init.c \
$(SRCDIR)/utils/ft_utils2.c \
$(SRCDIR)/utils/ft_utils.c \
$(SRCDIR)/utils/try_free.c \
$(SRCDIR)/utils/ft_realloc.c \
$(SRCDIR)/utils/ft_utils3.c \
$(SRCDIR)/utils/free.c \
$(SRCDIR)/utils/log_err.c \
$(SRCDIR)/utils/arg_split.c \
$(SRCDIR)/builtins/print_info.c \
$(SRCDIR)/builtins/inbuilt_check.c \
$(SRCDIR)/builtins/export_unset.c \
$(SRCDIR)/builtins/change_directory.c \
$(SRCDIR)/builtins/echo.c \
$(SRCDIR)/printf_fd/ft_printf.c \
$(SRCDIR)/printf_fd/basic_print.c \
$(SRCDIR)/environment/expand_env.c \
$(SRCDIR)/environment/env_list.c \
$(SRCDIR)/environment/update_array.c \
$(SRCDIR)/wildcard/paren.c \
$(SRCDIR)/wildcard/interpret.c \
$(SRCDIR)/wildcard/wildcard.c \
$(SRCDIR)/sighandling/sighandling.c \
$(SRCDIR)/error/error_codes.c \
$(SRCDIR)/tokens/token_utils.c \
$(SRCDIR)/tokens/token_check.c

IMPHDR	:=	$(LIBDIR)/libft/headers/libft.h

LIB		:=	$(shell find $(LIBDIR) -depth 1 -type d)
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(BUILDIR)/%.o)

CLNDIR	:=	$(IDRDIR) $(NAME)
FCLN	:=	$(BUILDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	gcc
COMFLAG	=	-Wall -Wextra -Werror -std=c99 -D_POSIX_C_SOURCE -I $(HDRDIR)

CFLAGS	=	$(COMFLAG) -g
LFLAGS	=	$(COMFLAG)
RLFLAGS =	-I/usr/local/opt/readline/include
RLLIB	=	-L/usr/local/opt/readline/lib

################################################################################
#								EXTERNAL UTILITIES							   #
################################################################################
RM		=	rm -rf
MKDIR	=	mkdir -p
CP		=	cp

################################################################################
#								LIBRARIES									   #
################################################################################
L42DIR	=	$(LIBDIR)/libft
LIB42	=	$(L42DIR)/libft.a
READLN	=	-lreadline

ALLLIB	=	$(LIB42) $(READLN)

################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs libs $(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@printf "Made directories: %s\n" $(TEMPDIR)

libs:
	@$(CP) $(IMPHDR) $(IDRDIR)
	@$(MAKE) -C $(L42DIR)
	@printf "Imported header: %s\n" $(IMPHDR)
	@printf "Libraries made: %s\n" $(LIB)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) $(RLFLAGS) $(RLLIB) -o $@ $(ALLLIB)
	@printf "Built program %s successfully\n" $@

$(BUILDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) $(RLFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(RM) $(CLNDIR)
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean: clean
	@$(RM) $(FCLN)
	@printf "Cleaned: %s\n" $(FCLN)

re: fclean all
	@printf "Cleaned and remade all files!\n"

jordan: #Pushes to Jordan's Github repo
	@git remote set-url origin https://github.com/t0mmusic/minishell.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

git: #Pushes to vogsphere repo
	@git remote set-url origin https://github.com/t0mmusic/minishell.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;
	@git remote set-url origin git@vogsphere.42adel.org.au:vogsphere/intra-uuid-91f3746f-03fa-49f0-a4d0-414e65deb8a5-4152683-nervin
	git push;

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 16:30:35 by Nathanael         #+#    #+#              #
#    Updated: 2022/07/07 09:47:12 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

################################################################################
#								DIRECTORIES									   #
################################################################################
BUILDIR	=	./build
HDRDIR	=	./headers
LIBDIR	=	./libraries
OBJDIR	=	./objects
SRCDIR	=	./sources
IDRDIR	=	./headers/imported

TEMPDIR =	$(OBJDIR) $(BUILDIR) $(IDRDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	$(shell find $(SRCDIR) -name '*.c')
IMPHDR	:=	$(shell find $(LIBDIR)/** -name '*.h')
LIB		:=	$(shell find $(LIBDIR) -depth 1 -type d)
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CLNDIR	:=	$(IDRDIR) $(BUILDIR)
FCLN	:=	$(OBJDIR)

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
LIB42	=	$(L42DIR)/build/libft.a
READLN	=	-lreadline

ALLLIB	=	$(LIB42) $(READLN)

################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs libs $(BUILDIR)/$(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@clear
	@printf "Made directories: %s\n" $(TEMPDIR)

libs:
	@$(CP) $(IMPHDR) $(IDRDIR)
	@$(MAKE) -C $(L42DIR)
	@clear
	@printf "Imported header: %s\n" $(IMPHDR)
	@printf "Libraries made: %s\n" $(LIB)

$(BUILDIR)/$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) $(RLFLAGS) $(RLLIB) -o $@ $(ALLLIB)
	@clear
	@printf "Built program %s successfully\n" $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) $(RLFLAGS) -c $< -o $@
	@clear
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(RM) $(CLNDIR)
	@clear
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean: clean
	@$(RM) $(FCLN)
	@printf "Cleaned: %s\n" $(FCLN)

re: fclean all
	@clear
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
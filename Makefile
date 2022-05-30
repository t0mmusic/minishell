# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 22:20:48 by Nathanael         #+#    #+#              #
#    Updated: 2022/05/30 16:24:52 by Nathanael        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

################################################################################
#								DIRECTORIES									   #
################################################################################
BUILDIR	=	./build
HDRDIR	=	./headers
OBJDIR	=	./objects
SRCDIR	=	./sources

TEMPDIR =	$(OBJDIR) $(BUILDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	$(shell find $(SRCDIR) -name '*.c')
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CLNDIR	:=	$(BUILDIR)
FCLN	:=	$(OBJDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	clang
COMFLAG	=	-Wall -Wextra -Werror -std=c99 -I $(HDRDIR)

CFLAGS	=	$(COMFLAG) -g
LFLAGS	=	$(COMFLAG)

################################################################################
#								EXTERNAL UTILITIES							   #
################################################################################
RM		=	rm -rf
MKDIR	=	mkdir -p
CP		=	cp

################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs $(BUILDIR)/$(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@clear
	@printf "Made directories: %s\n" $(TEMPDIR)

$(BUILDIR)/$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@ $(ALLLIB)
	@clear
	@printf "Built program %s successfully\n" $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) -c $< -o $@
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

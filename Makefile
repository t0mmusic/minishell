# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 16:30:35 by Nathanael         #+#    #+#              #
#    Updated: 2022/06/06 14:21:45 by Nathanael        ###   ########.fr        #
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
#								LIBRARIES									   #
################################################################################
L42DIR	=	$(LIBDIR)/libft
LIB42	=	$(L42DIR)/build/libft.a

ALLLIB	=	$(LIB42)

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

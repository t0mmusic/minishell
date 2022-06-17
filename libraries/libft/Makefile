# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 23:45:33 by Nathanael         #+#    #+#              #
#    Updated: 2022/06/17 12:01:25 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	libft.a

################################################################################
#								DIRECTORIES									   #
################################################################################
BLDDIR	=	./build
HDRDIR	=	./headers
LIBDIR	=	./libraries
OBJDIR	=	./objects
SRCDIR	=	./sources

TEMPDIR	=	$(BLDDIR) $(OBJDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	$(shell find $(SRCDIR) -name '*.c')
HEADERS	:=	$(shell find $(HDRDIR) -name '*.h')
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CLNDIR	:=	$(BLDDIR)
FCLN	:=	$(OBJDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -std=c99 -I $(HDRDIR)

################################################################################
#								EXTERNAL UTILITIES							   #
################################################################################
RM		=	rm -rf
MKDIR	=	mkdir -p
CP		=	cp

MAKELIB	=	ar -rcs

################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs $(BLDDIR)/$(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@clear
	@printf "Made directories: %s\n" $(TEMPDIR)

$(BLDDIR)/$(NAME): $(OBJECTS)
	@$(MAKELIB) $@ $^
	@clear
	@printf "Library %s built successfully\n" $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) -c $< -o $@
	@clear
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(RM) $(CLNDIR)
	@clear
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean:
	@$(RM) $(FCLN)
	@clear
	@printf "Cleaned: %s\n" $(FCLN)

re: clean all
	@clear
	@printf "Cleaned and remade all files!\n"

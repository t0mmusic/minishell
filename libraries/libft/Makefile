# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 23:45:33 by Nathanael         #+#    #+#              #
#    Updated: 2022/07/14 18:45:30 by Nathanael        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	libft.a

################################################################################
#								DIRECTORIES									   #
################################################################################
BLDDIR	=	./build
HDRDIR	=	./headers
LIBDIR	=	./libraries
SRCDIR	=	./sources

TEMPDIR	=	$(BLDDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	\
$(SRCDIR)/libc/ft_strnstr.c \
$(SRCDIR)/libc/ft_isdigit.c \
$(SRCDIR)/libc/ft_strlcpy.c \
$(SRCDIR)/libc/ft_strlen.c \
$(SRCDIR)/libc/ft_memcmp.c \
$(SRCDIR)/libc/ft_strchr.c \
$(SRCDIR)/libc/ft_bzero.c \
$(SRCDIR)/libc/ft_isascii.c \
$(SRCDIR)/libc/ft_memcpy.c \
$(SRCDIR)/libc/ft_isprint.c \
$(SRCDIR)/libc/ft_toupper.c \
$(SRCDIR)/libc/ft_strrchr.c \
$(SRCDIR)/libc/ft_isalpha.c \
$(SRCDIR)/libc/ft_memchr.c \
$(SRCDIR)/libc/ft_memset.c \
$(SRCDIR)/libc/ft_strncmp.c \
$(SRCDIR)/libc/ft_memmove.c \
$(SRCDIR)/libc/ft_strlcat.c \
$(SRCDIR)/libc/ft_atoi.c \
$(SRCDIR)/libc/ft_isalnum.c \
$(SRCDIR)/libc/ft_tolower.c \
$(SRCDIR)/memory/ft_calloc.c \
$(SRCDIR)/output/ft_putstr_fd.c \
$(SRCDIR)/output/ft_putnbr_fd.c \
$(SRCDIR)/output/ft_putendl_fd.c \
$(SRCDIR)/output/ft_putchar_fd.c \
$(SRCDIR)/list/ft_lstadd_back.c \
$(SRCDIR)/list/ft_lstnew.c \
$(SRCDIR)/list/ft_lstlast.c \
$(SRCDIR)/list/ft_lstclear.c \
$(SRCDIR)/list/ft_lstiter.c \
$(SRCDIR)/list/ft_lstmap.c \
$(SRCDIR)/list/ft_lstsize.c \
$(SRCDIR)/list/ft_lstadd_front.c \
$(SRCDIR)/list/ft_lstdelone.c \
$(SRCDIR)/string/ft_striteri.c \
$(SRCDIR)/string/ft_strjoin.c \
$(SRCDIR)/string/ft_strncmp_end.c \
$(SRCDIR)/string/ft_split.c \
$(SRCDIR)/string/ft_substr.c \
$(SRCDIR)/string/ft_strmapi.c \
$(SRCDIR)/string/ft_strtrim.c \
$(SRCDIR)/string/ft_strdup.c \
$(SRCDIR)/string/ft_itoa.c \
$(SRCDIR)/string/ft_strcmp.c

HEADERS	:=	\
$(HDRDIR)/libft.h

OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(BLDDIR)/%.o)

CLNDIR	:=	$(NAME)
FCLN	:=	$(BLDDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -std=c99 -MD -g3 -I $(HDRDIR)

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

all: dirs $(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@printf "Made directories: %s\n" $(TEMPDIR)

$(NAME): $(OBJECTS)
	@$(MAKELIB) $@ $^
	@printf "Library %s built successfully\n" $@

$(BLDDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(RM) $(CLNDIR)
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean:
	@$(RM) $(FCLN)
	@printf "Cleaned: %s\n" $(FCLN)

re: clean all
	@printf "Cleaned and remade all files!\n"

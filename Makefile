# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: garm <garm@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/08/26 23:49:31 by garm              #+#    #+#              #
##   Updated: 2015/01/17 09:15:52 by garm             ###   ########.fr       ##
#                                                                              #
# **************************************************************************** #

CC = g++

NAME = ft_rtype

LD_RUNPATH_SEARCH_PATHS = ~/SFML-2.1

SOURCES_DIR = src
INCLUDES_DIR = -I ~/SFML-2.1/include -I ./include

ifeq ($(DEBUG), 1)
	FLAGS = -g -Wall -Wextra
	CC = g++
else
	FLAGS = -Wall -Werror -Wextra
endif

LIBS = -L ~/SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#LIBS = ~/SFML-2.1/lib/libsfml-graphics.dylib ~/SFML-2.1/lib/libsfml-system.dylib ~/SFML-2.1/lib/libsfml-window.dylib

CFLAGS += $(FLAGS) $(INCLUDES_DIR)

DEPENDENCIES = \

SOURCES = \
		  $(SOURCES_DIR)/main.cpp \
		  $(SOURCES_DIR)/collision.cpp \

OBJS = $(SOURCES:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(DEPENDENCIES)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	@echo Creating $(NAME)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo Deleting $(NAME) OBJECTS files...

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM
	@echo Deleting $(NAME)...

re: fclean all

.PHONY: clean fclean re all


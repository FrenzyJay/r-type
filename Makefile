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

ifeq ($(USER), ato)
	LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif
ifeq ($(USER), jvincent)
	LIBS = -L ~/SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif
# ADD YOUR CONFIG HERE :)

CFLAGS += $(FLAGS) $(INCLUDES_DIR)

DEPENDENCIES = \

SOURCES = \
			$(SOURCES_DIR)/main.cpp \
			$(SOURCES_DIR)/Collision.cpp \
			$(SOURCES_DIR)/GameEngine.cpp \
			$(SOURCES_DIR)/GameEntity.cpp \
			$(SOURCES_DIR)/Player.cpp \
			$(SOURCES_DIR)/Projectile.cpp \
			$(SOURCES_DIR)/Enemy.cpp \
			$(SOURCES_DIR)/EnemyProjectile.cpp \

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


##
## Makefile for  in /home/dugast_a//CPP/Bomberman/bomberman-gredu/trunk/Ant
## 
## Made by antoine dugast
## Login   <dugast_a@epitech.net>
## 
## Started on  Thu May  2 11:14:27 2013 antoine dugast
## Last update Fri Jun  7 22:18:53 2013 louis cailleux
##

NAME		=	Bomberman

DIR		=	src

INC		=	include

LIB		=	./libgdl_gl-2012.4

SRC		=	$(DIR)/AObjects.cpp	\
			$(DIR)/APlayers.cpp	\
			$(DIR)/Air.cpp		\
			$(DIR)/Bomb.cpp		\
			$(DIR)/Bonus.cpp	\
			$(DIR)/Ashes.cpp	\
			$(DIR)/Camera.cpp	\
			$(DIR)/Menu.cpp		\
			$(DIR)/Computer.cpp	\
			$(DIR)/Exception.cpp	\
			$(DIR)/Floor.cpp	\
			$(DIR)/Human.cpp	\
			$(DIR)/IronWall.cpp	\
			$(DIR)/Map.cpp		\
			$(DIR)/Mutex.cpp	\
			$(DIR)/ReadFile.cpp	\
			$(DIR)/ScopedLock.cpp	\
			$(DIR)/Score.cpp	\
			$(DIR)/Timer.cpp	\
			$(DIR)/Utils.cpp	\
			$(DIR)/Vector3f.cpp	\
			$(DIR)/WoodWall.cpp	\
			$(DIR)/MyGame.cpp	\
			$(DIR)/Save.cpp		\
			$(DIR)/Parser.cpp	\
			$(DIR)/main.cpp		\
			$(DIR)/LavaWall.cpp	\
			$(DIR)/Explosion.cpp	\
			$(DIR)/Sound.cpp

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-g -W -Wall -Werror -Wextra -I$(INC) -I$(LIB)/include

LDFLAGS		=	-L$(LIB)/lib -Wl,--rpath=$(LIB)/lib -lgdl_gl -lGL -lGLU -lpthread -lsfml-audio

DUST		=	$(DIR)/*~ $(DIR)/\#*\# *~ \#*\# $(INC)/*~ $(INC)/\#*\#

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(LDFLAGS) $(OBJ)

dust		:
			$(RM) $(DUST)

clean		:	dust
			$(RM) $(OBJ)

fclean		:	clean 
			$(RM) $(NAME)

re		:	fclean all
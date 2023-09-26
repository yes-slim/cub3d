# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 20:51:44 by yes-slim          #+#    #+#              #
#    Updated: 2023/09/22 14:34:50 by yes-slim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER  	= -Iincludes  -I/usr/include -Imlx_linux -O3
MLX			= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lbsd
SANITIZ		= -fsanitize=address
CFLAGS 		= -Wall -Werror -Wextra -g3 $(SANITIZ) $(HEADER) -c 
NAME    	= cub3d
DEL     	= rm -rf
#=================parsing_files=======================================#
PARS 		= 
Pars_SRCS   = $(addsuffix .c, $(addprefix parsing/, $(PARS))) 
#=================execution_files=======================================#
LIBFT   	= _split
HELPERS 	= 
RC			= $(addprefix libft/, $(LIBFT)) \
	 	  	  $(addprefix helpers/, $(HELPERS))
			  
RC_SRCS   	= $(addsuffix .c, $(addprefix raycasting/, $(RC)))
#==================Scrs===============================================#
SRCS		= $(RC_SRCS) $(Pars_SRCS)
#====================================================================#
OBJ     	= $(SRCS:.c=.o)
#=========================compile=============================#
%.o     : %.c
		 @echo $(grey)$(italic)"	~Compiling $<"$(reset)
		 @cc $(CFLAGS) $< -o $@ 
#==========================rules==============================#
all     : $(NAME)

$(NAME) : $(OBJ) cub3d.c
		 @ar -rc cub3d.a $(OBJ)
		 @cc $(SANITIZ) cub3d.c cub3d.a $(HEADER) -o $(NAME) $(MLX)
		 @echo $(green)$(bold)":::$(NAME) is ready:::"$(reset)

clean  :
		 @echo $(grey)$(italic)$(bold)":::Deleting object files:::"$(reset)
		 @$(DEL) $(OBJ) cub3d.a
		 @echo $(red)$(bold)":::Deleted:::"$(reset)

fclean : clean
		 @echo $(grey)$(italic)$(bold)":::Deleting executeable:::"$(reset)
		 @$(DEL) $(NAME)
		 @echo $(red)$(bold)":::All deleted:::"$(reset)

re 	  : fclean all

.PHONY	: all clean fclean re
#===========================colors============================#
black  		= "\033[0;30m"
red    		= "\033[0;31m"
green  		= "\033[0;32m"
yellow 		= "\033[0;33m"
blue   		= "\033[0;34m"
purple		= "\033[0;35m"
cyan  		= "\033[0;36m"
grey   		= "\033[0;90m"
reset  		= "\033[0m"
#============================font=============================#
bold     	= "\033[1m"
italic    	= "\033[3m"
underline 	= "\033[4m"
inverse   	= "\033[7m"
#=============================================================#
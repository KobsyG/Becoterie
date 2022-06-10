MAP_STD		= std_map

MAP_FT		= ft_map

MAP_SRCS	= map_tester.cpp

MAP_OBJS	= ${MAP_SRCS:.cpp=.o}

CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

INCLUDES	= map_iterator.hpp map.hpp pair.hpp tree_iterator.hpp tree.hpp

all:		map

map:		${MAP_OBJS}

			$(CC) $(CFLAGS) -D STD -c $(MAP_SRCS) -I.${INCLUDE} -o $(MAP_OBJS)
			${CC} ${CFLAGS} -o ${MAP_STD} ${MAP_OBJS}

			$(CC) $(CFLAGS) -D FT -c $(MAP_SRCS) -I.${INCLUDE} -o $(MAP_OBJS)
			${CC} ${CFLAGS} -o ${MAP_FT} ${MAP_OBJS}

			./${MAP_STD} > std_map_out.txt
			./${MAP_FT} > ft_map_out.txt

			diff ft_map_out.txt std_map_out.txt > diff.txt
			# paste -d "|" ft_map_out.txt std_map_out.txt
			# cat diff.txt

clean:
			${RM} ${MAP_OBJS} ${MEGA_OBJS}

fclean:		clean
			${RM} ${MAP_FT} ${MAP_STD} diff.txt ft_map_out.txt std_map_out.txt

re:			fclean all



# SRCS		= main.cpp

# INCLUDES	= map.hpp tree.hpp node.hpp pair.hpp

# OBJS		= ${SRCS:.cpp=.o}

# NAME		= yes

# CC			= clang++
# CFLAGS		= -Wall -Wextra -Werror -std=c++98

# %.o:		%.cpp ${INCLUDES}
# 			${CC} ${CFLAGS} -o $@ -c $<

# all:		${NAME}

# ${NAME}:	${OBJS}
# 			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

# clean:
# 			${RM} ${OBJS}

# fclean:		clean
# 			${RM} ${NAME}

# re:			fclean all
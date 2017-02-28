
NAME 	= thread

DEBUG	= -g
CC		= gcc -c
LD 		= gcc
CFLAGS	= $(DEBUG) -W -Wall
LIBS 	= -lpthread -lm
LDFLAGS	= $(DEBUG)

OBJS	= main.c matrices.o synchronize.o get_time.o


all: $(NAME)

$(NAME): $(OBJS)
		$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(NAME)

main.o:			main.c matrices.h
matrices.o:		matrices.c matrices.h synchronize.h
synchronize.o: 	synchronize.c synchronize.h
get_time.o: 	get_time.c get_time.h
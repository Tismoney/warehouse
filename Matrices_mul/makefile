
NAME 	= thread

DEBUG	= -g
CC		= gcc -c
LD 		= gcc
CFLAGS	= $(DEBUG) -W -Wall
LIBS 	= -lpthread -lm
LDFLAGS	= $(DEBUG)

OBJS	= main.o matrices/matrices.o synchronize/synchronize.o get_time/get_time.o


all: $(NAME)

$(NAME): $(OBJS)
		$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(NAME)

main.o:			main.c matrices/matrices.o
matrices/matrices.o:		matrices/matrices.c matrices/matrices.h synchronize/synchronize.h
synchronize/synchronize.o: 	synchronize/synchronize.c synchronize/synchronize.h
get_time/get_time.o: 	get_time/get_time.c get_time/get_time.h
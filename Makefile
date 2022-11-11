CC		= g++
CFLAGS	= -g
TATGET	= cpp-crow
SRCS	= main.cpp
OBJS	= $(SRCS:.cpp=.o)
INCDIR	= -I.
LIBS	= -lpthread

$(TATGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

run :
	./$(TATGET)

all : clean $(OBJS) $(TATGET)

clean:
	rm -f $(OBJS) $(TATGET)
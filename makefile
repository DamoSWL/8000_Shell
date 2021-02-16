
CC = g++
LD = g++


SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = shell

.PHONY:all clean


all: $(TARGET)


$(TARGET): $(OBJS)
	$(LD) -o $@ $^

%.o:%.c
	$(CC) -c $^


clean:
	rm -f $(OBJS) $(TARGET)
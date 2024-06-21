CC= x86_64-w64-mingw32-gcc
CFLAGS= -Wall -g
SRCS=oss_phase1.c
TARGET=Num_Baseball 
OBJS := $(patsubst %.c,%.o,$(SRCS))

all : $(TARGET) 
%.o:%.c
	$(CC) $(CCFLAGS) $< -c -o $@
$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@


.PHONY=clean

clean:
	rm -f $(OBJS) $(TARGET) 

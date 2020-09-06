CC = gcc
CFLAGS = -g
TARGET = mydu
OBJS = main.o depthfirstapply.o 
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(JOBS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
depthfirstapply.o: depthfirstapply.c
	$(CC) ($CFLAGS) -c depthfirstapply.c
clean:
	/bin/rm -f *.o $(TARGET)


CC = gcc
CFLAGS = -g
TARGET = mydu
OBJS = main.o depthfirstapply.o sizepathfun.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
depthfirstapply.o: depthfirstapply.c
	$(CC) $(CFLAGS) -c depthfirstapply.c
sizepathfun.o: sizepathfun.c
	$(CC) $(CFLAGS) -c sizepathfun.c
clean:
	/bin/rm -f *.o $(TARGET)


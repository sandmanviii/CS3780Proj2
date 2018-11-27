CC=g++
TARGET=task1
OBJS=task1.o

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

task1.o:	task1.cpp
	$(CC) -c task1.cpp

clean:
	rm -f *.o $(TARGET)

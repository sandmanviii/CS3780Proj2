CC=g++ -I /usr/local/openssl/include -L /usr/local/openssl/lib
CFLAGS=-g
TARGET1=task1
TARGET2=task2
TARGET3=task3
OBJS1=task1.o
OBJS2=task2.o
OBJS3=task3.o

all: task1 task2 task3

$(TARGET1):	$(OBJS1)
	$(CC) -o $(TARGET1) $(CFLAGS) $(OBJS1) -lcrypto -lssl

$(TARGET2):	$(OBJS2)
	$(CC) -o $(TARGET2) $(CFLAGS) $(OBJS2) -lcrypto -lssl

$(TARGET3):	$(OBJS3)
	$(CC) -o $(TARGET3) $(CFLAGS) $(OBJS3) -lcrypto -lssl

task1.o:	task1.cpp
	$(CC) $(CFLAGS) -c task1.cpp 

task2.o:	task2.cpp
	$(CC) $(CFLAGS) -c task2.cpp 

task3.o:	task3.cpp
	$(CC) $(CFLAGS) -c task3.cpp 

clean:
	rm -f *.o $(TARGET1) $(TARGET2) $(TARGET3)

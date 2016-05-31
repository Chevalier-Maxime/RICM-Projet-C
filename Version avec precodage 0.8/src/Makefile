CC = gcc
OBJS = sdata.o compression.o decompression.o entete.o desentetage.o entete.o depretraitage.o lectureEcriture.o pretraitement.o main.o
EXEC = ../bin/Compresseur
CFLAGS = -Wall -I ../include
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	-rm -rf ./src/*.o

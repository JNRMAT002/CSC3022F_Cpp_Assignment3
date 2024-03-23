CC = g++
CCFLAGS = -std=c++11 #-static # flags passed to the compiler (this flag making use of C++11 features is required for this course)

all: ConnectedComponent PGMimageProcessor driver

driver: src/driver.cpp
	${CC} ${CCFLAGS} src/driver.cpp bin/ConnectedComponent.o bin/PGMimageProcessor.o -o bin/findComp

PGMimageProcessor: src/PGMimageProcessor.cpp include/PGMimageProcessor.h
	$(CC) ${CCFLAGS} -c src/PGMimageProcessor.cpp -o bin/PGMimageProcessor.o

ConnectedComponent: src/ConnectedComponent.cpp include/ConnectedComponent.h
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/ConnectedComponent.cpp -o bin/ConnectedComponent.o

run:
	./bin/findComp -t 128 -w -p cameraman.pgm

clean:
	@echo "Cleaning up..."
	rm bin/*
	rmdir bin
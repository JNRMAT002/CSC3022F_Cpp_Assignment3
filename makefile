CC = g++
CCFLAGS = -std=c++11 #-static # flags passed to the compiler (this flag making use of C++11 features is required for this course)

all: PGMimageProcessor driver

driver: src/driver.cpp
	${CC} ${CCFLAGS} src/driver.cpp bin/PGMimageProcessor.o -o bin/findComp

PGMimageProcessor: src/PGMimageProcessor.cpp include/PGMimageProcessor.h
	$(CC) ${CCFLAGS} -c src/PGMimageProcessor.cpp -o bin/PGMimageProcessor.o

run:
	./bin/findComp -s 3 9 -t 115 -w -p mona512.pgm

clean:
	@echo "Cleaning up..."
	rm bin/*.exe
	rm bin/*.o
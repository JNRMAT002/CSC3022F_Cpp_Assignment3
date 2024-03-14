CC = g++
CCFLAGS = -std=c++11 #-static # flags passed to the compiler (this flag making use of C++11 features is required for this course)

# all: hello for descending print prod sum unknown while

driver: src/driver.cpp
	${CC} ${CCFLAGS} src/driver.cpp -o bin/findComp

run:
	./bin/findComp -s 3 9 -t 120 -p -w mona512.pgm

clean:
	@echo "Cleaning up..."
	rm bin/*.exe
	rm bin/*.o
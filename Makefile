CC=g++

imageops: Image.o driver.o
	$(CC) driver.o Image.o -o imageops

Image.o: Image.cpp Image.h
	$(CC) -c Image.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp

test:
	$(CC) -c -o Image.o Image.cpp
	$(CC) -c -o ImageTest.o ImageTest.cpp
	$(CC) -o imagetest ImageTest.o Image.o

run-test:
	./imagetest

clean:
	rm -rf *.o imageops

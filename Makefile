CC=g++

imageops: Image.o driver.o
	$(CC) driver.o Image.o -o imageops

Image.o: Image.cpp Image.h
	$(CC) -c Image.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp

test:
	$(CC) -c -o Image.o Image.cpp --std=c++11 -w
	$(CC) -c -o ImageTest.o ImageTest.cpp --std=c++11 -w
	$(CC) -o imagetest ImageTest.o Image.o --std=c++11 -w

run-test:
	./imagetest

clean:
	rm -rf *.o imageops imagetest

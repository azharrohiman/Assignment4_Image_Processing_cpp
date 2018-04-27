CC=g++

imageops: Image.o driver.o
	$(CC) driver.o Image.o -o imageops

Image.o: Image.cpp Image.h
	$(CC) -c Image.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp

clean:
	rm -rf *.o imageops

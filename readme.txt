Muhammad Azhar Rohiman - RHMMUH005. CSC3022H - Assignment 4.

Instructions on how to compile, run and use the program:

1) cd to folder containing cpp and h files. 'cd Assignment4'

2) type 'make command' in terminal to create object and executable files

3) type 'make clean' to remove object and executable files

4) to run the program:
i.   for addition, type - 	./imageops -a Lenna_standard.pgm Lenna_hat_mask.pgm add.pgm
ii.  for subtraction, type - 	./imageops -s Lenna_standard.pgm Lenna_hat_mask.pgm subtract.pgm
iii. for inverting, type - 	./imageops -i Lenna_standard.pgm invert.pgm
iv.  for threshold, type - 	./imageops -t Lenna_standard.pgm 100 threshold.pgm
v.   for masking, type - 	./imageops -l Lenna_standard.pgm Lenna_hat_mask.pgm mask.pgm

The names of the pgm files are examples but they are given in the same directory as the source and exe files.

5) type 'make test' to compile the ImageTest.cpp file

6) to run the tests, type 'make run-test' in terminal

Feel free to contact me on rhmmuh005@myuct.ac.za if you encounter any issue. Thank you.

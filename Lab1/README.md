# Lab 1: “Super-fast” Sudoku Solving

##  **Basic version**

### 1. Overview

Implement a Sudoku solving program, using multiple threads or multiple processes, running on a single machine. Try to utilize all your CPU cores and make your program run as fast as possible!

### 2. Background

#### Introduction to Sudoku

Sudoku (originally called Number Place) is a logic-based combinatorial number-placement puzzle. You are given a 9×9 board of 81 squares logically separated into 9 columsn, 9 rows, and 9 3×3 subsquares. The goal is, given a board with some initial numbers filled in (we call it a Sudoku puzzle), fill in the rest of the board so that every column, row, and subsquare have all the digits from 1 to 9 and each digit appears only once (we call it a Sudoku solution).

### 3.Program input and output

#### 3.1   Compiler

A Makefile exists in the src folder and is compiled using the make tool. The make tool does and automatically maintains the compilation through a file called a Makefile, which describes the compilation and wiring rules for the entire project.

Before compiling, make sure you have the **make** tool and **g++** compiler on your machine. 

If this is your first time using this code, run the command make to compile.Like this:

```
jack@jack-virtual-machine:~/桌面/云计算/Lab1-1.3/src$ make
g++ -c neighbor.cc -O2 
g++ -c sudoku_dancing_links.cc -O2 
g++ -c sudoku_basic.cc -O2 
g++   -O2  -o sudoku_solve main.cc neighbor.o sudoku_dancing_links.o sudoku.h SDK.h sudoku_basic.o -lpthread
```

Running this command generates an executable file named suoku_solve.

Use **make clean** to delete the file you just compiled

```
jack@jack-virtual-machine:~/桌面/云计算/Lab1-1.3/src$ make clean
rm sudoku_dancing_links.o
rm neighbor.o
rm sudoku_basic.o
rm sudoku_solve
```



#### 3.2   Input

1. The program should have no arguments during start. For example, if your program is called sudoku_solve, just typing ./sudoku_solve and the program will run correctly. 
2.  Accept one input file name, and the size of the input file is smaller than 100MB.
3. In the input file, each line is a Sudoku puzzle that needs to be solved. Each line contains 81 decimal digits. The 1st-9th digits are the 1st row of the 9×9 grid, and the 10th-18th digits are the 2nd row of the 9×9 grid, and so on. Digit 0 means this digit is unknown and your program needs to figure it out according to the Sudoku rules described above.



Example input to your program may be like this (start your program and read 1 input file names from stdin)

```
jack@jack-virtual-machine:~/桌面/云计算/Lab1-1.3/src$ ./sudoku_solve
test1
```

If you use the above input method, the result is the default output to the screen. If we want to output the result of sudoku to a file, we can redirect the output. Input like the following:

```
jack@jack-virtual-machine:~/桌面/云计算/Lab1-1.3/src$ ./sudoku_solve >1.txt
test1
```

With this input, you can direct the output to the file 1.txt. If 1.txt does not exist in the current directory, you will create a new file and run it. The input file is test1000.

Example input file format,

```
./test1 is an input file that contains one Sudoku puzzle problem that need to be
solved:
000000010400000000020000000000050407008000300001090000300400200050100000000806000
The first Sudoku puzzle problem (first line) actually looks like this when being
placed on the 9×9 grid:
---------------------
0 0 0 | 0 0 0 | 0 1 0
4 0 0 | 0 0 0 | 0 0 0
0 2 0 | 0 0 0 | 0 0 0
---------------------
0 0 0 | 0 5 0 | 4 0 7
0 0 8 | 0 0 0 | 3 0 0
0 0 1 | 0 9 0 | 0 0 0
---------------------
3 0 0 | 4 0 0 | 2 0 0
0 5 0 | 1 0 0 | 0 0 0
0 0 0 | 8 0 6 | 0 0 0
---------------------
```

####  3.4  Output

Read the sudoku in the input file and output the final result to stdout. The default is output to the screen and, if redirected, to a file. Open the file and you'll see the results. The order of the output sudoku is the same as that of the input file.

Suppose the contents of the file in test1 are as follows

```
000000010400000000020000000000050407008000300001090000300400200050100000000806000
```

The following is an example of the output to the screen

```
jack@jack-virtual-machine:~/桌面/云计算/Lab1-1.3/src$ ./sudoku_solve
test1
693784512487512936125963874932651487568247391741398625319475268856129743274836159
```

### 4.The test file

The SRC folder contains 5 test files of different sizes. Test1, test10, test1000 test5000, test10000, test used for you.

### 5.The algorithm for solving sudoku puzzles

**Dancing Links**

If you want to learn about this algorithm, read the blog below

https://www.cnblogs.com/grenet/p/3145800.html

So solving a sudoku problem using the Dancing Links algorithm is actually the following process

1. Turn the sudoku problem into an accurate coverage problem

2. Design the data matrix

3. The accurate coverage problem is solved by the Dancing Links algorithm

4. Transform the solution of the exact coverage problem into a unique solution



### 6.Version of implementation

This code only implements the basic requirements.

1. Accept one input file name, and the size of the input file is smaller than 100MB. 

2. Successfully solve the puzzles in the input file, and output the results in the format described before. 
3. Use multiple threads/processes to make use of most of your machine's CPU cores.

### 7.The performance test report

The test report describe the test inputs, and the performance result under various testing conditions. Specifically, the test report contains the following two things: 

1. Compare the performance of  “super-fast” Sudoku solving program with a simple singlethread version, using the same input and under the same environment.
2.  Change the input (e.g., change file size) and environment (e.g., using machines with different CPUs and hard drives), and draw several curves of your program’s performance under various conditions.
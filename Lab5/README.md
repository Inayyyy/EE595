# lab-5-yanijinnn

## Author Information
Name: Yani Jin

Student ID: 3973887764

Email: yanijin@usc.edu

## Instructions to Compile and Run
- To compile the program, type `make` in terminal.
- To run this program, type `./Lab5_3973887764 input.txt` in the terminal.
    - The first prompt you will get will look like this: "Please enter the number of weeks (Integer between 0 and 52)", you just type in any integer belongs to [0, 52] to continue.
    - You will get the second line looks like this: "To solve it recursively, press R. To solve it iteratively, Press I", which is self-explained.
- IF you want to clean all unnecessary object file, or restart, you could type `make clean` in the terminal, then repeat the first two instructions to compile and run agian.

## Program Summary
- I take the first recommandation given by professor: Total profit of all possible cases / all possible cases = estimated average profit.
- To calculate all possible cases:
    - Base cases: C(0) = 0; C(1) = 1; C(2) = 2; C(3) = 4.
    - Recursion rule: C(n) = C(n-1) + C(n-2) + C(n-3).
- To calculate total profit of all possible cases: (F(n) is given by input file)
    - Base cases: P(0) = 0; P(1) = F(1); P(2) = 2*F(1) + F(2); P(3) = 3*F(1) + 2*(F(1) + F(2)) + F(3).
    - Recursion rule: P(n) = F(1) + P(n-1) + F(2) + P(n-2) + F(3) + P(n-3).

## Result
I provide both recursion and iteration solution. The result of them are consistent, but you will find the recursion solution runs is getting slowly when the input number of weeks is higher than 30.

The another thing I need to mention is that the estimated profit for Kanye West is growing slowly and even stop increasing as the input number of weeks increases. And so does Kourosh Yaghmaei's estimated profit, accordingly. All I do is following what I said in the **Program Summary** section, I'm not sure why it happens.

//CLASS: cs315-002 Fall 2022
//ASSIGNMENT: HW1
//STUDENT: Aaron Moseley
//SID: 99774
//DATE:  2/2/22
//PROBLEM: Find the answer to the formula f(n) = 3f(n - 1) - f(n - 2)
//ALGORITHM: Recursion
//RUNNING TIME: 
//COMPILATION: g++ Recursion.cpp -o Recursion
//SYNOPSIS:  ./Recursion n (treats the first argument as n)
//BUGS: No bugs found
//EXTRAS: N/A
//REFERENCES: N/A

#include <iostream>

int formula(int n)
{
	if(n <= 1)
	{
		return n;
	}

	return (3 * formula(n - 1)) - formula(n - 2);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		return 0;
	}

	int n = atoi(argv[1]);

	if(n < 0)
	{
		return 0;
	}

        std::cout << formula(n) << std::endl;

        return 0;
}

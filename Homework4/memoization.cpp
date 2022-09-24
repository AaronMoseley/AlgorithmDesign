//CLASS: cs315-002 Fall 2022
//ASSIGNMENT: HW4
//STUDENT: Aaron Moseley
//SID: 99774
//DATE:  2/2/22
//PROBLEM: Find the answer to the formula f(n) = 3f(n - 1) - f(n - 1)
//ALGORITHM: Memorization
//RUNNING TIME: 
//COMPILATION: g++ Memoization.cpp -o Memoization
//SYNOPSIS:  ./Memoization n mod (treats the first argument as n and prints the answer mod the second argument)
//BUGS: No bugs found
//EXTRAS: N/A
//REFERENCES: N/A

#include <iostream>

long answers[10000];

long formula(int n, int mod)
{
	if(n <= 1)
	{
		return n;
	}

	if(answers[n] != 0)
	{
		return answers[n];
	}

	answers[n] = (3 * (formula(n - 1, mod)) - formula(n - 2, mod)) % mod;

	return answers[n];
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		return 0;
	}

	int n = atoi(argv[1]);
	int mod = atoi(argv[2]);

	if(n < 0 || mod < 0)
	{
		return 0;
	}

	answers[0] = 0;
	answers[1] = 1;

	std::cout << formula(n, mod)<< std::endl;

	return 0;
}

//Class: CS315-002 Spring 2022
//Date: 03/19/2022
//Assignment: Project 1
//		-Read a pair of relatively prime numbers
//		-Encrypt a message using the multiplicative modular inverse of the two numbers
//		-Decrypt an encrypted message using the reverse technique
//Program Name: pa1774.cpp
//Author: Aaron Moseley
//SID: 49774
//Description:
//		-Takes in two numbers, a and N
//		-Tests that a < N and that they are relatively prime
//		-Encrypts a string using (ASCII values * a) % N
//		-Finds the multiplicative modular inverse of a and N
//		-Decrypts a given encrypted message using (given value * inverse) % N
//Compilation: g++ pa1774.cpp -o pa1774
//Environment:
//		-g++ -version: gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
//		-uname -a: Linux ajmo276 5.4.0-92-generic #103-Ubuntu SMP Fri Nov 26 16:13:00 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux 
//Synopsis: ./pa1774 < input1.txt
//		-input1.txt:
//		13 300
//		Welcome
//		256 61 37
//
//		-Output:
//		13 300
//		231 113 204 87 243 217 113
//		13 277 300
//		pa1
//
//	    ./pa1774 < input2.txt
//		-input2.txt:
//		673 1774
//		Aaron Moseley
//		1169 1417 440 195 1296 248 375 195 1113 561 1724 561 1603
//
//		-Output:
//		673 1774
//		1169 1417 440 195 1296 248 375 195 1113 561 1724 561 1603
//		Aaron Moseley
//
//Method: Multiplicative modular inverse encryption
//Running Time: O(nlog(n))
//Bugs: None
//Extras: Checks that a and N are relatively prime and that a < N, swaps a and N if a > N
//References: 
//		-https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
//		To review the Extended Euclidean Algorithm for inverse
//
//		-https://en.wikipedia.org/wiki/Euclidean_algorithm
//		To review Euclidean algorithm for gcd
//

#include <string>
#include <iostream>
#include <vector>

using namespace std;

string decryptText(unsigned int, unsigned int, vector<unsigned int>);
void encryptText(unsigned int, unsigned int, unsigned int*, string);
int inverse(int, int);
int gcd(unsigned int, unsigned int);

int main()
{
	//Define and read a and N
	unsigned int a, N;
	cin >> a >> N;

	//Check that a and N are relatively prime
	if(gcd(a, N) != 1)
	{
		cout << "Invalid Input" << endl;
		cout << gcd(a, N) << endl;
		return 0;
	}

	//Swaps a and N if a > N
	if(a > N)
	{
		unsigned int temp = a;
		a = N;
		N = temp;
	}

	//Clear cin to take in the input
	cin.ignore();
	cin.clear();


	//Define and read the input string
	string input;
	getline(cin, input);


	//Define and encrypt the encrypted text
	unsigned int encryptedText[input.length()];
	encryptText(a, N, encryptedText, input);


	//Print encrypted text
	for(int i = 0; i < input.length(); i++)
	{
		cout << encryptedText[i] << " ";
	}

	cout << endl;

	//Defines vector and reads input for the encrypted message
	vector<unsigned int> encrypted;
	string temp;
	getline(cin, temp);
	temp += ' ';

	//Separates the string into parts based on the space character, converts each part to an int and adds it to the vector
	while(temp.find(' ') != temp.length() - 1)
	{
		string temp1 = temp.substr(0, temp.find(' '));
		temp = temp.substr(temp.find(' ') + 1, temp.length());

		unsigned int temp2 = stoi(temp1);
		encrypted.push_back(temp2);
	}

	unsigned int temp2 = stoi(temp.substr(0, temp.length() - 1));
	encrypted.push_back(temp2);

	//Decrypts text
	string decryptedText = decryptText(a, N, encrypted);

	cout << decryptedText << endl;
	return 0;
} //main

void encryptText(unsigned int a, unsigned int N, unsigned int* encryptedText, string input)
{
	cout << a << " " << N << endl;	

	//Loop through the entirety of the input string
	for(int i = 0; i < input.length(); i++)
	{
		//Multiply each character by a and the modulo N for encryption
		encryptedText[i] = ((int)input[i] * a) % N;
	}
} //encryptText

string decryptText(unsigned int a, unsigned int N, vector<unsigned int> encryptedText)
{
	string result = "";

	//Finds inverse and prints the obligatory a, inverse, N
	int moduloInverse = inverse(a, N);
	cout << a << " " << moduloInverse << " " << N << endl;

	//Decrypts each character using (encryptedValue * inverse) % N
	for(int i = 0; i < encryptedText.size(); i++)
	{
		char nextChar = (char)((encryptedText[i] * moduloInverse) % N);
		result += nextChar;
	}

	return result;
} //decryptText

int inverse(int a, int n)
{	
	//Sets up necessary variables for calculations
	int matrix[2][3] = {{n, 1, 0}, {a, 0, 1}};
	int remainder;

	do{
		//Calculates the new elements of the matrix
		int quotient = matrix[0][0] / matrix[1][0];

		remainder = matrix[0][0] - (quotient * matrix[1][0]);
		int newS = matrix[0][1] - (quotient * matrix[1][1]);
		int newT = matrix[0][2] - (quotient * matrix[1][2]);

		//Shifts up the matrix and loads in new numbers
		for(int i = 0; i < 3; i++)
		matrix[0][i] = matrix[1][i];

		matrix[1][0] = remainder;
		matrix[1][1] = newS;
		matrix[1][2] = newT;
	} while(remainder != 0);

	//Makes the return value positive
	while(matrix[0][2] < 0)
	matrix[0][2] += n;

	return matrix[0][2];
} //inverse

int gcd(unsigned int a, unsigned int b)
{
	//Swaps a and b if input in wrong order
	if(a < b)
	{
		unsigned int temp = a;
		a = b;
		b = temp;
	}

	//Uses Euclidean algorithm to calculate gcd
	while(b != 0)
	{
		unsigned int mod = a % b;
		a = b;
		b = mod;
	}

	return a;
} //gcd

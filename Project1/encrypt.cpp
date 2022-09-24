//Class: CS315-002 Spring 2022
//Assignment: Project 1 Milestone 2
//Student: Aaron Moseley
//SID: 49774
//Date: 03/11/2022
//Problem: Encrypt a string
//Compilation: g++ encrypt.cpp -o encrypt
//Synopsis: ./encrypt (No input on command line, input numbers/characters as directed once the program is running)
//Method: Multiplicative modular inverse encryption
//Running Time: O(n)
//Bugs: None
//Extras: None
//References: Took some inspiration from the speaker in class on Thursday

#include <string>
#include <iostream>

using namespace std;

void encryptText(unsigned int, unsigned int, unsigned int*, string);

int main()
{
	//Define and read a and N
	unsigned int a, N;

	cout << "Please input a and N separated by a space." << endl;
	cin >> a >> N;


	//Clear cin to take in the input
	cin.ignore();
	cin.clear();


	//Define and read the input string
	string input;

	cout << "Please input the string to encrypt." << endl;
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

	return 0;
} //main

void encryptText(unsigned int a, unsigned int N, unsigned int* encryptedText, string input)
{
	//Loop through the entirety of the input string
	for(int i = 0; i < input.length(); i++)
	{
		//Multiply each character by a and the modulo N for encryption
		encryptedText[i] = ((int)input[i] * a) % N;
	}
} //encryptText

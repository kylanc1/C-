/*
Name: Kylan Coffey
Class: CSCI 1410
Description: PA2
Status: successfully compiled and ran
//Function Prototypes
//Function Implementations
*/

//NOTE: I put functions.h and functions.cpp in the same file as "coffeyKPA2.cpp" to make it easier to grade. 

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <limits>
#include <stdio.h>      
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

//functions.h
#pragma once
#ifndef CUSTOMRESPONSE_H
#define CUSTOMRESPONSE_H
struct CustomResponse
{
	string response;
	string responseType;
};
#endif //CUSTOMRESPONSE_H

//functions.h
#pragma once
#ifndef CUSTOMRESPONSEFUNCTIONS_H
#define CUSTOMRESPONSEFUNCTIONS_H
void ReadInResponses(ostream &out, CustomResponse  CustomResponseArray[], int &currentSize);
CustomResponse newCustomResponse(istream &in);
void listResponses(ostream &out, CustomResponse  CustomResponseArray[], int &currentSize);
std::fstream& GotoLine(std::fstream& file, unsigned int num);
#endif //CUSTOMRESPONSEFUNCTIONS_H

//functions.cpp
void ReadInResponses(ostream &out, CustomResponse CustomResponseArray[], int &currentSize)
{
	//Read From File
	string line;
	string ReadIn;
	int num;
	num = 0;
	ifstream myfile("CustomResponses.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			line = ReadIn;
			num = num + 1;
		}
		cout << "\nRead in " << num << " lines from CustomResponses.txt" << endl << endl;
		myfile.close();
	}
}

//functions.cpp
CustomResponse newCustomResponse(istream &in)
{
	CustomResponse CustomResponse1;
	cout << "Enter Custom Response: ";
	in.ignore();
	getline(in, CustomResponse1.response);
	cout << "\nResponse Type (Positive: Type 'Positive', Negative: Type 'Negative', Vauge: Type 'Vauge')";
	getline(in, CustomResponse1.responseType);
	cout << endl;
	ofstream myfile("CustomResponses.txt", std::ofstream::out | std::ofstream::app);
	if (myfile.is_open())
	{
		cout << endl;
		myfile << CustomResponse1.response << endl;
		myfile << CustomResponse1.responseType << endl;
		cout << endl;
		myfile.close();
	}
	else cout << "Unable to open file 'CustomResponses.txt' ";

	return CustomResponse1;
}

//functions.cpp
bool addCustomResponse(CustomResponse responseToAdd, CustomResponse CustomResponseArray[], int &currentSize, const int MAXSIZE)
{
	currentSize++;
	if (currentSize < MAXSIZE)
	{
		CustomResponseArray[currentSize - 1] = responseToAdd;
		return true; //successful add
	}
	else
		return false;
}

//functions.cpp
void listResponses(ostream &out, CustomResponse CustomResponseArray[], int &currentSize)
{
	//Read From File
	string line;
	ifstream myfile("CustomResponses.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "Could not open 'CustomResponses.txt'" << endl;
}

//functions.cpp
std::fstream& GotoLine(std::fstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num + 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

//coffeyKPA2.cpp
int main()
{
	char menu;
	int randNum;
	char cont = 'n';
	const int MAXSIZE = 100;
	int currentSize = 0;
	CustomResponse CustomResponse1;
	CustomResponse CustomResponseArray[MAXSIZE];
	string line;
	string ReadIn;
	bool done = false;
	while (!done)
	{
	Menu:
		cout << "a.Read responses from a file\n";
		cout << "b.Play Magic Eight Ball\n";
		cout << "c.Add responses to a file\n";
		cout << "d.Print out responses\n";
		cout << "e.Exit" << endl;
		cin >> menu;
		switch (menu)
		{
		case 'A':
		case 'a':
			ReadInResponses(cout, CustomResponseArray, currentSize);
			break;
		case 'B':
		case 'b':
			while (cont != 'N' || cont != 'n')
			{
				int numOfQuestions = 0;
				cout << "How many questions would you like to ask?" << endl;
				cin >> numOfQuestions;
				for (int i = 0; i < numOfQuestions; i++) {
					//Question
					cout << "\nAsk a Question: ";
					string question;
					cin >> question;

					//Read From File to get line num
					string lineNum;
					int num = 0;
					ifstream myfile("CustomResponses.txt");
					if (myfile.is_open())
					{
						while (getline(myfile, lineNum))
						{
							num = num + 1;
						}
					}
					else
						cout << "Could not open 'CustomResponses.txt'" << endl;
					//Number Generation
					randNum = 3 + (2 * rand()) % num; //dynamic number to update the number to however many lines are in the text file

					//Answer
					fstream file("CustomResponses.txt");
					GotoLine(file, randNum);
					getline(file, line);
					cout << "Answer: " << line << endl;
					myfile.close();
					}
				cout << endl;
			goto Menu;
			}
		case 'C':
		case 'c': 
			CustomResponse1 = newCustomResponse(cin);
			addCustomResponse(CustomResponse1, CustomResponseArray, currentSize, MAXSIZE);
			break;
		case 'D':
		case 'd':
			listResponses(cout, CustomResponseArray, currentSize);
			break;
		case 'E':
		case 'e': 
			exit(0);
			break;
		
		default: cout << "Choose a letter between A and E\n";
		}//switch
	}//while
}//main
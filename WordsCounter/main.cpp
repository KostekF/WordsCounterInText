/**
* \file main.cpp
* \author Filip Kostecki
* \date 18-09-18
*/


#include<iostream>
#include<list>
#include<vector>
#include"WordsCounter.h"
using namespace std;


int main()
{	
	
	WordsCounter w1("mobyDick.txt");
	fstream outputFile;
	outputFile.open("OutputFile.csv", ios::out);
	if (outputFile.is_open())
	{
		cout << "Connected to file: " << "OutputFile.txt" << endl;
	}
	if (outputFile.is_open() && w1.isConnected())
	{
		w1.collectData();
		w1.saveDataToFile(outputFile);
		outputFile.close();
		cout << "File " << "OutputFile.txt" << " closed!" << endl;
	}
	

	cout << endl;
	system("pause");
	return 1;

}


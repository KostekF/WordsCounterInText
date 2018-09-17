/**
* \file WordsCounter.cpp
* \author Filip Kostecki
* \date 18-09-18
*/


#include "WordsCounter.h"

using namespace std;

void WordsCounter::acquireWords() 
{
	string tmp = "";

	while (m_inputFile >> tmp)
	{
		m_lWords.push_back(make_pair(tmp, 0));
	}
	cout << "Text acquired from file " << m_inputFileName << endl;
}

void WordsCounter::removeDelimiters()
{
		for (auto itr = m_lWords.begin(); itr != m_lWords.end(); ++itr)
		{
			if (!itr->first.empty())
			{
				for (auto jtr = itr->first.begin(); jtr != itr->first.end(); ++jtr)
				{
					if ((*jtr >= 'a' && *jtr <= 'z') || (*jtr >= 'A' && *jtr <= 'Z'))
					{
					}
					else
					{
						if (itr->first.size() == 1)
						{
							itr->first.erase(jtr); break;
						}
						else
						{
							jtr = itr->first.erase(jtr);
						}

						if (jtr != itr->first.begin())
						{
							jtr--;
						}
					}
				}
			}
			else
			{
				itr = m_lWords.erase(itr);
				if (itr != m_lWords.begin())
				{
					itr--;
				}
			}
		}
	

	
	}

bool WordsCounter::connectToFile(fstream& file)
{
	file.open(m_inputFileName, ios::in);
	if (file.is_open())
	{
		cout << "Connected to file " << m_inputFileName << endl;
		return true;
	}
	else return false;
}



void WordsCounter::countUniqueWords()
{
	for (auto itr = m_lWords.begin(); itr != m_lWords.end(); ++itr) //maybe change to lower only first charatcer instead of iterating over all string
	{
			transform(itr->first.begin(), itr->first.end(), itr->first.begin(), ::tolower);
	}
	m_lWords.sort();
	list<pair<string, int>> lTmpList;
	int counter = 0;
	auto tmpItr = m_lWords.begin();
	auto itr = m_lWords.begin();
	advance(itr, 1);
	for (; itr != m_lWords.end(); ++itr,++tmpItr)
	{
		if (itr->first != tmpItr->first)
		{
			lTmpList.push_back(make_pair(tmpItr->first, counter));
			counter = 1;
		}
		else ++counter;
	}
	cout << "Counted unique words from acquired text\n";
	
	m_lWords = lTmpList;

}

 bool WordsCounter::sortByCounter(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second)
{
	if (first.second > second.second) return true;
	else return false;
}



 bool WordsCounter::isConnected()
 {
	 return m_inputConnected;
 }

 void WordsCounter::collectData()
 {
	 auto start = chrono::steady_clock::now();
	 acquireWords();
	 auto end = chrono::steady_clock::now();
	 auto diff = end - start;
	 // print the measured time in milliseconds:]
	 cout << "Acquiring words(time): ";
	 cout << chrono::duration < double, milli >(diff).count() << " ms" << endl;
	 

	 start = chrono::steady_clock::now();
	 removeDelimiters();
	 end = chrono::steady_clock::now();
	 diff = end - start;
	 cout << "Removing delimeters(time): ";
	 cout << chrono::duration < double, milli >(diff).count() << " ms" << endl;


	 start = chrono::steady_clock::now();
	 countUniqueWords();
	 end = chrono::steady_clock::now();
	 diff = end - start;
	 cout << "Counting unique words(time): ";
	 cout << chrono::duration < double, milli >(diff).count() << " ms" << endl;

	 start = chrono::steady_clock::now();
	m_lWords.sort(sortByCounter);
	end = chrono::steady_clock::now();
	diff = end - start;
	cout << "Sorted words by frequency of appearing(time)";
	 cout << chrono::duration < double, milli >(diff).count() << " ms" << endl;
	 
 }

 void WordsCounter::saveDataToFile(ostream & outStream)
 {
	 for (auto itr = m_lWords.begin(); itr != m_lWords.end(); ++itr)
	 {
		 outStream << itr->first << ';'<< itr->second << endl;
	 }
	 cout << "Saved data to output file" << endl;
 }

 WordsCounter::WordsCounter(string fileName):m_inputFileName(fileName)
{
	m_inputConnected=connectToFile(m_inputFile);
}

WordsCounter::~WordsCounter()
{
	if (m_inputConnected)
	{
		m_inputFile.close();
		cout << "File " << m_inputFileName << " closed" << endl;
	}

}

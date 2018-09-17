/**
* \file WordsCounter.h
* \author Filip Kostecki
* \date 18-09-18
*/

//! Short: WordsCounter acquires words and creates statistics of them.

/**
* WordsCounter class acquires words from *.txt file created by user,
  removes non-letters from words(e.g. delimeters) and counts how many times every single word appeared in text.
  Lastly it sorts words in descending order and prints those statistics to *.csv file given by user.
*/
#ifndef __WordsCounter
#define __WordsCounter

#include<list>
#include<fstream>
#include<string>
#include<iostream>
#include<algorithm>
#include<chrono>
class WordsCounter
{
private:
	
	std::list<std::pair<std::string,int>> m_lWords; ///< Holds every word from text and its frequency of appearing(list of pairs(uniqueWord,numOfAppearance)
	std::string m_inputFileName; ///< Holds a name of input  *.txt  file
	std::fstream m_inputFile; ///<  Holds input file ..
	bool m_inputConnected; ///< Holds true if connection with input file was established, otherwise=false

private:
	bool connectToFile(std::fstream& file); //! Method connects to file with given fstream& file as argument. So far uses private attribute as argument. Maybe change that? 
	void acquireWords(); //! Method acquires every word from input file and stores them in list
	void removeDelimiters();//! Method removes delimeters(e.g. commas at the end of a word) from words in list

	/**
	Method counts unique words, merges repeating identical words and stores frequency of appearing of every word in list.
	Possible flaw: method has to change every letter tolower
	*/
	void countUniqueWords();//! Method for counting unique words in list
	
	
	static bool sortByCounter(const std::pair<std::string, int> &first, const std::pair<std::string, int>& second); //! sorting descending comparasion function for list sort. 

public:
	bool isConnected(); //! Checks if connection was established
	void collectData(); //! Function uses other private functions to collect words, work on them and check time of processing by chrono lib 

	/**
	\param outStream param comes from *.csv file
	*/
	void saveDataToFile(std::ostream& outStream); //! Saves data to given by user *.csv file

	/*! \brief Constructor takes name of *.txt file 
	*    on which statistics will be made
	*/
	WordsCounter(std::string fileNameInput);
	~WordsCounter();
};

#endif
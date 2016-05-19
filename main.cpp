/*Ryan Hayes
  Spring 2016
  This program uses a Spellchecker Class
  To return if a word is spelled correctly.
  If it is not spelled correctly, it returns
  a list of suggested words which fall within
  a certain edit distance. */

#include "SpellChecker.h"
#include <iostream>
#include <list>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	SpellChecker s("lexicon.txt");
	bool hasPrinted = false;
	int distance = 2;
	if(argv[1] != NULL){distance = atoi(argv[1]);}

	while(hasPrinted != true)
	{
		std::string str;	

		std::cout << "Enter a word: ";
		std::cin >> str;

		if(!s.spelledCorrectly(str))//if the word is not spelled correctly
		{
			std::list<std::string> suggestedWords = s.suggestWords(str, distance);//find suggested words
			if(suggestedWords.empty())//if there are no suggestions
			{
				std::cout << "No suggestions" << std::endl;
			} 
			else
			{
				while(!suggestedWords.empty())//while we havent gone through the whole list
				{
					std::cout << suggestedWords.back() << std::endl;//print each suggested word
					suggestedWords.pop_back();
					hasPrinted = true;
				}
			}
		}
		else
		{
			std::cout << "Correctly Spelled" << std::endl;		
		}
	}
	return 0;
}

/*Ryan Hayes
  Spring 2016
  This SpellChecker class uses a BK tree
  in order to tell if a word inputted by the user
  is spelled correctly. If it is not, it traverses
  that tree and constructs a list of words that
  fall within a user inputted edit distance.
*/

#include <string>
#include <map>
#include <list>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

class SpellChecker
{
private:
	class LCBKTree
	{
	private:
		class BKTreeNode
		{
			std::string word_;
			std::map<int, BKTreeNode> childMap_;
		public:
			BKTreeNode(std::string word);
			BKTreeNode();

		protected:
			friend class LCBKTree;
		};

		BKTreeNode* root_;
		size_t size_;

	public:
		LCBKTree();
		~LCBKTree();
		
		/*Adds a node to the bk tree*/
		void insert(std::string word);
		
		/*returns a list containing words that fall within maxDis*/
		std::list<std::string> lookup(std::string word, int maxDis);

	private:
		//helper functions for lookup and insert
		void lookup(BKTreeNode* root, std::string word, int maxDis, std::list<std::string>& suggestedWords);
		void insert(BKTreeNode*& root, std::string word);
	};
public:

	SpellChecker(std::string lexiconFile);
	virtual ~SpellChecker(void);

	/*returns an edit distance between two words*/
	static int editDistance(std::string userWord, std::string lexiconWord);
	
	/*finds the mininmum of three ints*/
	static int threeMin(int x, int y, int z);

	/*Returns true if userWord is spelled correctly*/
	bool spelledCorrectly(std::string userWord);

	/*this method returns a list of words that fall within an edit distance*/
	std::list<std::string> suggestWords(std::string userWord, int distance);

	//std::list<std::string> listSuggestWords(std::string userWord, int distance);

private:
	//std::list<std::string> readIn(std::string lex);

	/*This method reads a lex file into the lexiconTree*/
	void BKReadIn(std::string lex);

private:
	//std::list<std::string> lexicon_;
	LCBKTree lexiconTree_;
};


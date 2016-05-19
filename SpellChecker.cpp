#include "SpellChecker.h"

//BKTree methods
SpellChecker::LCBKTree::LCBKTree()
{
	root_ = NULL;
	size_ = 0;
}

SpellChecker::LCBKTree::~LCBKTree()
{
}

//driver function for insert
void SpellChecker::LCBKTree::insert(std::string word)
{
	insert(root_, word);
}

//helper function for insert
void SpellChecker::LCBKTree::insert(BKTreeNode*& root, std::string word)
{
	if(root == NULL)
	{
		size_ = 1;
		root = new BKTreeNode(word);
	}
	else 
	{
		int ed = editDistance(word, root->word_);
		if(ed > 0)
		{
			BKTreeNode* subRoot = &root->childMap_[ed];
			if(subRoot->word_ == "")//if childMap constructed a default node
			{			//then a word does not exist at that edit distance
				subRoot->word_ = word;//change that string to match word
				++size_;
			}
			else//a word exists at that edit distance
			{
				insert(subRoot,word);//recurse on current root
			}
		}
	}	
}

//driver function for lookup
std::list<std::string> SpellChecker::LCBKTree::lookup(std::string word, int maxDis)
{
	std::list<std::string> retList;
	lookup(root_, word, maxDis, retList);
	return retList;
}

//helper function for lookup
void SpellChecker::LCBKTree::lookup(BKTreeNode* root, std::string word, int maxDis, std::list<std::string>& suggestedWords)
{
	int ed = editDistance(word, root->word_);//find bounds
	int maxBound = maxDis + ed;
	int minBound = maxDis - ed;
	if(minBound <= 0) { minBound = 1;}

	for(std::map<int, BKTreeNode>::iterator it= root->childMap_.begin(); it != root->childMap_.end(); ++it)
	{
		if(it->first >= minBound && it->first <= maxBound)//if element falls within bounds
		{
			if(editDistance(it->second.word_, word) <= maxDis)//if word falls within edit distance
			{
				suggestedWords.push_front(it->second.word_);//add to suggested words
			}
			lookup((&(it->second)), word, maxDis, suggestedWords);//recurse on children that fall within bounds
		} 
	}	
}

//BKTreeNode Methods
SpellChecker::LCBKTree::BKTreeNode::BKTreeNode()
{
	word_ = "";
	
}

SpellChecker::LCBKTree::BKTreeNode::BKTreeNode(std::string word) 
	: word_(word)
{
}


//Spellchecker methods
SpellChecker::SpellChecker(std::string lexiconFile)
{
	BKReadIn(lexiconFile);
}

SpellChecker::~SpellChecker(void)
{

}

int SpellChecker::threeMin(int x, int y, int z)//return min of three ints
{
	return std::min(std::min(x, y), z);
}

int SpellChecker::editDistance(std::string userWord, std::string lexiconWord)
{
	int m = userWord.length();
	int n = lexiconWord.length();
    	// Create a table to store results of subproblems
    	int dp[m+1][n+1];

	for (int i = 0; i <= m; i++)
    	{
    		for (int j = 0; j <= n; j++)
        	{
            		if (i == 0)//if we havent made progresss
	    		{
                		dp[i][j] = j;//then distance will be length of second string (all of j is set to 0 initially)
            		}
            		else if (j == 0)
	    		{
                		dp[i][j] = i; // Min. operations = i (all of i set to 0 initially)
            		}
            		else if (userWord[i-1] == lexiconWord[j-1])//if last characters are the same 
	    		{
                		dp[i][j] = dp[i-1][j-1];//then ignore those characters and continue
	    		}	
            		else//if last characters are different
	    		{
                		dp[i][j] = 1 + threeMin(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]); // consider all possibilities and find min
	    		}
        	}
    	}
    	return dp[m][n];
}

bool SpellChecker::spelledCorrectly(std::string userWord)
{	
	//if lookup finds no word with 0 differences, userWord isnt spelled correctly
	return (lexiconTree_.lookup(userWord, 0).size() == 1);
}

std::list<std::string> SpellChecker::suggestWords(std::string userWord, int distance)
{
	return lexiconTree_.lookup(userWord, distance);
}

//read in for BKTree
void SpellChecker::BKReadIn(std::string lex)
{
        std::ifstream file(lex.c_str());//convert to char string so it can be read

        std::string word;

        while(getline(file, word))      //while we havent reached the end of a line
        {
                lexiconTree_.insert(word);//push back the line
                word = "";
        }
}

/* Below are methods that are used for spellchecking with a list vs a BK tree
//read in for list
std::list<std::string> SpellChecker::readIn(std::string lex)
{
	std::list<std::string> wordList;

        std::ifstream file(lex.c_str());//convert to char string so it can be read

        std::string word;

        while(getline(file, word))      //while we havent reached the end of a line
        {
                wordList.push_back(word);//push back the line
                word = "";
        }
        return wordList;
}

//suggestwords for list
std::list<std::string> SpellChecker::listSuggestWords(std::string userWord, int distance)
{
        std::list<std::string> retList;
        //List suggest words
        std::list<std::string>::iterator it = lexicon_.begin();
        while(it != lexicon_.end())
        {
                if(editDistance(userWord, *it) <= distance)
                {
                        retList.push_front(*it);
                }
                ++it;
        }

        return retList;

}*/


/*     This is Spellchecker.

	When the user enters a mispelled word, Spellchecker will provide a list of
	words from a given lexicon provided that the lexicon contains words that
	fall within the user-specified edit distance of the mispelled word.
	Otherwise Spellchecker will return  no suggestions.

	The edit distance is how many changes to letters are required to convert a
	specified word to a new word.  For example, the edit distance between the
	words "Cat" and "Cate" would be one as the only change required would be
	to delete the "e" in "Cate". The edit distance between "fated" and "ate"
	would be two as both the  "f" and "d" in "fated" would have to be removed.

	This edit distance is specified in the command line when the program is
	first run.

	For example, "./spellchecker 3" would run the program with a default edit
	distance of 3.
*/

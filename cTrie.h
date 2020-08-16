#include <string>
#include <list>
#include <set>

#ifndef C_TRIE_H
#define C_TRIE_H

#define ALPHABET_SIZE 26
#define NOT_SYMBLE -2



char codeToSymbol(int code); 
int symbolToCode(char c); //defines the allowing symbols



class cTrieVertex
{
private:
	std::set<int> mActiveChildren; //consists numbers of existing vertexes
	cTrieVertex* mChildren[ALPHABET_SIZE];
	cTrieVertex* mParent;
	bool mIsWord;

	void deleteChild(int code);
	void deleteChildren();

public:
	cTrieVertex();
	~cTrieVertex() { deleteChildren();}

	bool isWord() const { return mIsWord; }
	bool hasChild(int code) const { return mChildren[code] != nullptr; }
	cTrieVertex* getChild(int code) const { return mChildren[code]; }

	void markAsWord() { mIsWord = true; }
	void addChild(int code);

	friend class cTrie;
};



class cTrie
{
private:
	cTrieVertex* mRoot;
	cTrieVertex* mCur; //for character-by-character processing

	cTrieVertex* findSubstring(const std::string& s) const;
	cTrieVertex* findWord(const std::string& word) const;
	void getWords(const cTrieVertex& v, std::string& curWord, std::list<std::string>& words) const;

public:
	cTrie() { mRoot = new cTrieVertex(); mCur = mRoot; }
	~cTrie() { delete mRoot; mCur = mRoot = nullptr; }

	void add(const std::string& s);
	void processChar(char c, bool backSpace, std::string& begin, int& distFromTrie);
};



class cTrieException
{
private:
	std::string description;

public:
	cTrieException(std::string s) { description = s; }
	std::string what() { return description; }

};

#endif // !C_TRIE_H
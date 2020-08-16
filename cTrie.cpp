#include <vector>
#include <iostream>
#include "cTrie.h"




int symbolToCode(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	else
		return NOT_SYMBLE;
}



char codeToSymbol(int code)
{
	if (code >= 0 && code <= ALPHABET_SIZE)
		return 'a' + code;
	else
		return NOT_SYMBLE;
}




cTrieVertex::cTrieVertex()
{
	mIsWord = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		mChildren[i] = nullptr;
	mParent = nullptr;
}



void cTrieVertex::addChild(int code)
{ 
	mActiveChildren.insert(code);
	mChildren[code] = new cTrieVertex();
	mChildren[code]->mParent = this;
}



void cTrieVertex::deleteChild(int code)
{ 
	mActiveChildren.erase(code);
	mChildren[code]->mParent = nullptr;
	delete mChildren[code]; 
	mChildren[code] = nullptr;
}



void cTrieVertex::deleteChildren()
{ 
	for (int code = 0; code < ALPHABET_SIZE; code++) 
	{ 
		if (hasChild(code)) 
			deleteChild(code);
	}
}



void cTrie::add(const std::string& s)
{	
	cTrieVertex* cur = mRoot;
	int code;

	for(int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if ((code = symbolToCode(c)) != NOT_SYMBLE)
		{
			if (cur->hasChild(code))
				cur = cur->getChild(code);

			else
			{
				cur->addChild(code);
				cur = cur->getChild(code);
			}
			if (i == s.size() - 1)
				cur->markAsWord();
		}
		else 
			throw cTrieException("Unknown symbol.");
	}
}



cTrieVertex* cTrie::findSubstring(const std::string& s) const
{
	cTrieVertex* cur = mRoot;
	int code;

	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if ((code = symbolToCode(c)) != NOT_SYMBLE)
		{
			if (cur->hasChild(code))
				cur = cur->getChild(code);
			else
				return nullptr;
		}
		else
			throw cTrieException("Unknown symbol.");
	}
	return cur;
}



cTrieVertex* cTrie::findWord(const std::string& word) const
{
	cTrieVertex* found = findSubstring(word);
	if (found != nullptr && found->isWord()) 
		return found; 
	else 
		return nullptr;
}



void cTrie::getWords(const cTrieVertex& v, std::string& end, std::list<std::string>& ends) const
{
	if (v.isWord())
		ends.push_back(end);
	if (v.mActiveChildren.empty())
	{
		if(!end.empty())
			end.pop_back();
		return;
	}

	for(auto &code: v.mActiveChildren)
	{
		end.push_back(codeToSymbol(code));
		getWords(*(v.mChildren[code]), end, ends);
	}

	if (!end.empty())
		end.pop_back();
	return;
}



void cTrie::processChar(char c, bool backSpace, std::string& request, int& distFromTrie)
{
	bool noHits = false;
	if(backSpace)
	{
		if (request.empty())
		{
			std::cout << "Input is empty.\n";
			return;
		}

		else
		{
			request.pop_back();
			if (distFromTrie == 0)
				mCur = mCur->mParent;
			else
				distFromTrie--;

			if (distFromTrie > 0)
				noHits = true;
		}
	}

	else
	{
		int code = symbolToCode(c);
		if (code != NOT_SYMBLE)
		{
			request.push_back(c);
			if (mCur->hasChild(code))
				mCur = mCur->mChildren[code];
			else
			{
				noHits = true;
				distFromTrie++;
			}
		}
		else
		{
			if (c == '_')
			{
				mCur = mRoot;
				request.clear();
				std::cout << "Space\n";
				return;
			}

			else
			{
				std::cout << "Unknown symbol.\n";
				return;
			}
		}
	}

	std::cout << "Your request: " << request << "\n";
	if(!noHits)
	{
		std::string	end = "";
		std::list<std::string> ends;

		getWords(*mCur, end, ends);

		std::cout << "Hits:\n";
		for (auto& en : ends)
			std::cout << request + en << "\n";
	}
	else
	{
		std::cout << "No hits!\n";
	}
}
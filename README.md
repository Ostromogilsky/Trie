# Trie
Console prototype of the dictionary with trie-based search. May be update to search bar GUI with history.

The file "cTrie.cpp" contains realization of trie class.
Firstly, define your alpabet with

char codeToSymbol(int code) and
int symbolToCode(char c).

Then add words with

void cTrie::add(const std::string& s).

Then use

void cTrie::processChar(char c, bool backSpace, std::string& request, int& distFromTrie)

for character-by-character processing and prefix searching

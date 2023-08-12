//
// Created by mdrib on 8/7/2023.
//

#include <fstream>
#include "Trie.h"

void Trie::addWord(const basic_string<char>& word) {
    shared_ptr<Node> currentNode = root;
    for (char character : word) {
        if (! currentNode->hasCharacter(character)) {
            currentNode->children->emplace(character, make_shared<Node>(false));
        }
        currentNode = currentNode->getNextNode(character);
    }

    currentNode->isEndOfWord = true;
}

bool Trie::hasWord(const basic_string<char>& word) {
    shared_ptr<Node>& currentNode = root;
    for (char character : word) {
        if (! currentNode->hasCharacter(character)) return false;

        currentNode = currentNode->getNextNode(character);

    }
    return currentNode->isEndOfWord;
}

vector<string> Trie::getAllWords(const basic_string<char>& letters,
                                 function<void(const string&)> actionUponFindingWord) {
//    vector<string> returnValue;
//    queue<string> combinations;
//    int index = 0;
//
//
//    do {
//
//    } while (index < returnValue.size());

//    return vector<sting>();
}

vector<string> Trie::getAllWordsOfLength(int length) {

}

Trie::Trie() {
    root = make_shared<Node>(false);
}

void Trie::updateTrieUsingFile(const basic_string<char> &fileWithWords, function<bool(const string &)> isAddable,
                               Trie& trie) {
    ifstream file(fileWithWords);
    int counter = 0;
    string str;

    if (!file.is_open()) {
        throw invalid_argument("The parameter 'fileWithWords' is not valid. That file could not be opened!");
    }

    // Adding the words from the file to the trie
    while (!file.eof()) {
        getline(file, str, ' ');

        if (isAddable(str)) {
            counter++;
            trie.addWord(str);
        }
    }
    if (file.is_open()) {
        file.close();
    }
}

Trie::~Trie() {
//    cout << "Destructor Called ;0 !\n";

}

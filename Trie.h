//
// Created by mdrib on 8/7/2023.
//

#ifndef WORDLE_PLAYER_TRIE_H
#define WORDLE_PLAYER_TRIE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <queue>

using namespace std;

class Trie {
public:
    virtual void addWord(const basic_string<char> &word);

    virtual bool hasWord(const basic_string<char> &word);
    vector<string> getAllWords(const basic_string<char> &letters, function<void(const string&)> actionUponFindingWord);
    vector<string> getAllWordsOfLength(int length);
    void updateTrieUsingFile(const basic_string<char>& fileWithWords, function<bool(const string&)> isAddable, Trie& trie);
    Trie();
    ~Trie();

protected:
    class Node {
    public:
        bool isEndOfWord; // Whether this TrieNode is the end of the word
        // All the children of 'this' Node object. I am using pointers, so they stay on the Heap (I need alot and so they
        // don't go out of scope and succumb to the garbage collector)
        shared_ptr<unordered_map<char, shared_ptr<Node>>> children;

        Node(bool isEndOfWord) : isEndOfWord(isEndOfWord) {
            children = make_shared<unordered_map<char, shared_ptr<Node>>>();
        }

        bool hasCharacter(char ch) {
            return children->find(ch) != children->end();
        }

        shared_ptr<Node> getNextNode(char &ch) { return (*children)[ch]; }
    };
public:
    shared_ptr<Node> root;
};


#endif //WORDLE_PLAYER_TRIE_H

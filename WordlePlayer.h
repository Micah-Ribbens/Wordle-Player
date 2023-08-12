//
// Created by mdrib on 8/8/2023.
//

#ifndef WORDLE_PLAYER_WORDLEPLAYER_H
#define WORDLE_PLAYER_WORDLEPLAYER_H
#include "Trie.h"
#include <memory>

class WordlePlayer : public Trie {
public:
    WordlePlayer(string fileWithWords, function<bool(const string&)> isAddable);
    string getBestPlay();
    void update(string result);
    void addWord(const basic_string<char> &word) override;
    bool hasWord(const basic_string<char> &word) override;
    void resetValidGuesses();

private:
    unordered_map<basic_string<char>, int> probabilities;
    Trie trie;
    vector<char> possibleLetters;
    string allLetters = "abcdefghijklmnopqrstuvwxyz";
    unordered_map<string, bool> validGuesses;
    unordered_map<int, vector<char>> indexToValidCharacters;
    string previousGuess;

    void resetProbabilities();
    void makeAllInvalid(char character);
    void makeCharacterOnlyOption(int index, char character);

    class CombinationObject {
    public:
        string value;
        shared_ptr<Node> node;

        CombinationObject(string value, shared_ptr<Node> node) : value(value), node(node) {};
    };
    void runCombinationAdder(string& combination, queue<CombinationObject>& combinations, shared_ptr<Node>& currentCombinationNode);

// For Debugging
public:
    void printIndexToValidCharacters();
    void setPreviousGuess(string value) { previousGuess = value; }
};


#endif //WORDLE_PLAYER_WORDLEPLAYER_H

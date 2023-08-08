//
// Created by mdrib on 8/8/2023.
//

#ifndef WORDLE_PLAYER_WORDLEPLAYER_H
#define WORDLE_PLAYER_WORDLEPLAYER_H
#include "Trie.h"

class WordlePlayer : Trie {
public:
    WordlePlayer(string fileWithWords, function<bool(const string&)> isAddable);
    string getBestPlay();
    void update(string result);
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

// For Debugging
public:
    void printIndexToValidCharacters();
    void setPreviousGuess(string value) { previousGuess = value; }
};


#endif //WORDLE_PLAYER_WORDLEPLAYER_H

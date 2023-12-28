//
// Created by mdrib on 8/8/2023.
//

#ifndef WORDLE_PLAYER_WORDLESIMULATOR_H
#define WORDLE_PLAYER_WORDLESIMULATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "WordlePlayer.h"
using namespace std;


class WordleSimulator {
public:
    WordleSimulator(const string& pathToPastWordleWords, WordlePlayer& wordlePlayer);
    void simulateAllWords(int counter=-1);
    int getNumberOfGuesses(const string& word);
    string getResult(string actualWord, string guess);
private:
    vector<string> pastWordleWords;
    WordlePlayer wordlePlayer;
};


#endif //WORDLE_PLAYER_WORDLESIMULATOR_H

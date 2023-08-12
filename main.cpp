#include "WordlePlayer.h"

//
// Created by mdrib on 8/7/2023.
//
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "WordleSimulator.h"

using namespace std;

int main() {

    string currentPath = filesystem::current_path().string();
    // The currentPath is to cmake-build-debug, which is not wanted. The path should be to the same directory as main.cpp
    int incorrectStart = currentPath.rfind("\\") + 1; // The last slash is needed for the path
    string correctedPath = currentPath.substr(0, incorrectStart);

    auto isAddable = [](const string& value) { return value.length() == 5;};

    WordlePlayer wordlePlayer(correctedPath + "english_words.txt", isAddable);
    wordlePlayer.setPreviousGuess("wards");
    wordlePlayer.update("w*rds");
    wordlePlayer.setPreviousGuess("aeoiu");
    wordlePlayer.update("--*--");
//    wordlePlayer.printIndexToValidCharacters();
//    WordleSimulator wordleSimulator(correctedPath + "five_letter_words.txt", wordlePlayer);
//    wordleSimulator.getNumberOfGuesses("words");
//    cout << wordleSimulator.getResult("words", "sword");
}
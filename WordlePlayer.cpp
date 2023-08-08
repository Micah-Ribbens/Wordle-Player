//
// Created by mdrib on 8/8/2023.
//

#include "WordlePlayer.h"

WordlePlayer::WordlePlayer(std::string fileWithWords, function<bool(const string&)> isAddable) {
    trie = getTrieFromFile(fileWithWords, isAddable);
    resetProbabilities();

    for (auto character : allLetters) {
        for (int i = 0; i <= 4; i++) {
            validGuesses[character + to_string(i)] = true;
        }
    }

}

string WordlePlayer::getBestPlay() {

    // TODO update previousGuess
}

void WordlePlayer::resetProbabilities() {
    probabilities.clear();
    for (auto character : allLetters) {
        for (int i = 0; i <= 4; i++) {
            // Doing the to_string(i) to convert it into a string
            probabilities.emplace(character + to_string(i), 0);
        }
    }
}

void WordlePlayer::update(string result) {
    int index = 0;
    unordered_map<char, int> characterToAmountInWord;
    for (auto character : previousGuess) {
        characterToAmountInWord.emplace(character, 0);
    }

    for (auto character : previousGuess) {
        characterToAmountInWord[character]++;
    }

    for (const auto& resultCharacter : result) {
        char guessCharacter = previousGuess[index];
        int amountOfCharacterInWord = characterToAmountInWord[guessCharacter];

        if (resultCharacter == '-' && amountOfCharacterInWord == 1) {
            makeAllInvalid(guessCharacter);
            cout << "Make All Invalid " + string(1, guessCharacter) + "\n";
        }
        else if (resultCharacter == '*' || resultCharacter == '-') {
            // The result and the characters lineup
            validGuesses[guessCharacter + to_string(index)] = false;
        }
        else { // Meaning that the correct letter was guessed
            makeCharacterOnlyOption(index, guessCharacter);
        }

        index++;
    }

    indexToValidCharacters.clear();
    for (int i = 0; i <= 4; i++) {
        indexToValidCharacters[i] = vector<char>();
    }
    for (const auto& pair : validGuesses) {
        bool isValidGuess = pair.second;

        if (isValidGuess) {
            int index2 = stoi(string(1, pair.first[1]));
            char character = pair.first[0];
            indexToValidCharacters[index2].emplace_back(character);
        }
    }
}

void WordlePlayer::makeAllInvalid(char character) {
    for (int i = 0; i <= 4; i++) {
        validGuesses[character + to_string(i)] = false;
    }
}

void WordlePlayer::makeCharacterOnlyOption(int index, char character) {
    for (auto ch : allLetters) {
        validGuesses[ch + to_string(index)] = false;
    }
    validGuesses[character + to_string(index)] = true; // Updating the value of the actual valid character
}

void WordlePlayer::printIndexToValidCharacters() {
    string printedValue = "{\n";

    for (auto pair : indexToValidCharacters) {
        printedValue += to_string(pair.first) + ": [ ";

        sort(pair.second.begin(), pair.second.end());
        for (auto value : pair.second) {
            printedValue += string(1, value) + ", ";
        }
        printedValue += "]\n";
    }
    printedValue += "\n}";
    cout << printedValue;
}



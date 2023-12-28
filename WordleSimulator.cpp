//
// Created by mdrib on 8/8/2023.
//

#include "WordleSimulator.h"
WordleSimulator::WordleSimulator(const std::string& pathToPastWordleWords, WordlePlayer& wordlePlayer)
                                : wordlePlayer(wordlePlayer) {

    ifstream file(pathToPastWordleWords);
    string str;

    if (!file.is_open()) {
        throw invalid_argument("The parameter 'pathToPastWordleWords' is not valid. That file could not be opened!");
    }

    // Adding the past wordle words to the list
    while (!file.eof()) {
        getline(file, str, '\n');

        // Making all the letters lowercase
        transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        pastWordleWords.push_back(str);
        if (!wordlePlayer.hasWord(str)) {
            wordlePlayer.addWord(str);
        }
    }

    if (file.is_open()) {
        file.close();
    }
}

void WordleSimulator::simulateAllWords(int maxCounter) {
    unordered_map<int, int> guesses; // {numberOfGuesses: number of words guessed with the amount 'numberOfGuesses'}

    int defaultValue = -1;
    if (maxCounter == defaultValue) {
        maxCounter = pastWordleWords.size();
    }

    int counter = 0;

    for (const auto& word : pastWordleWords) {
        int numberOfGuesses = getNumberOfGuesses(word);

        if (guesses.find(numberOfGuesses) == guesses.end()) {
            guesses.emplace(numberOfGuesses, 1);
        }

        guesses[numberOfGuesses]++;
        counter++;

        if (counter == maxCounter) {
            break;
        }
        cout << numberOfGuesses << "\n";
    }

    string printedString = "{\n";

    for (auto pair : guesses) {
        printedString += to_string(pair.first) + ": " + to_string(pair.second) + ",";
    }
    cout << printedString << "\n}";
}

int WordleSimulator::getNumberOfGuesses(const string& word) {
    wordlePlayer.resetValidGuesses();
    int counter = 1;
    // If it goes longer than 50 then something is off (usual should be close to 4)
    while (counter < 50) {
        string bestPlay;
        try {
            bestPlay = wordlePlayer.getBestPlay();
        }
        catch (bad_alloc badAlloc) {
            cout << "Bad Alloc from best play!!!";
        }
        if (word == bestPlay) {
            cout << "It guessed it in " + to_string(counter) + " guesses!\n";
            break;
        }
        wordlePlayer.update(getResult(word, bestPlay));
        wordlePlayer.resetValidGuesses();
        counter++;
//        cout << getResult(word, bestPlay);
//        break;
    }

    if (counter >= 50) {
        cout << "This is bad! It should take at max 6, but usually 4 \n";
    }

    return counter;

}

string WordleSimulator::getResult(string actualWord, string guess) {
    string returnValue;
    int index = 0;

    for (const char& character : guess) {
        if (actualWord[index] == guess[index]) {
            returnValue += character;
        } else if (actualWord.find(character) != string::npos) {
            returnValue += "*";
            actualWord.erase(std::remove_if(actualWord.begin(), actualWord.end(),
                                       [returnValue](char c) { return to_string(c) == returnValue; }),
                        actualWord.end());
        } else {
            returnValue += "-";
        }
        index++;
    }
    return returnValue;
}

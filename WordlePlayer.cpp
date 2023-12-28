//
// Created by mdrib on 8/8/2023.
//

#include "WordlePlayer.h"

WordlePlayer::WordlePlayer(std::string fileWithWords, function<bool(const string&)> isAddable) {
    updateTrieUsingFile(fileWithWords, isAddable, trie);

    resetProbabilities();
    resetValidGuesses();
}

string WordlePlayer::getBestPlay() {
    resetProbabilities();
    queue<CombinationObject> combinations;

    shared_ptr<Node>& trieRoot = trie.root;

    // Filling the queue with preliminary values, so the do while loop works properly
    for (auto& letter : indexToValidCharacters[0]) {
        if (trieRoot->hasCharacter(letter)) {
            combinations.emplace(string(1, letter), trieRoot->getNextNode(letter));
        }
    }
    int amount = 0;
    string currentCombination;

    try {
        // Finding all the possible combinations and updating the probabilites (points) for each letter and location
        while (true) { // Truthfully should never occur, but this is a safety
            amount++;

            if (amount >= 100'000) {
                cout << "Very bad. Taking way too long!!!!";
                cout << to_string(combinations.size()) + "\n";
                break;
            }

            if (combinations.empty()) {

                cout << "Ah Crap !!!! " + currentCombination;
                throw invalid_argument("Combinations never updated or something " + to_string(amount));
            }

            currentCombination = combinations.front().value;

            // End condition for the loop to terminate
            if (currentCombination.length() == 5) {
                break;
            }

            shared_ptr<Node>& currentCombinationNode = combinations.front().node;
            combinations.pop();

            // Creating more combinations
            int index = currentCombination.length(); // We need to look for the next letters in the combination

            for (auto& letter : indexToValidCharacters[index]) {
                if (currentCombinationNode->hasCharacter(letter)) {
                    string newCombination = currentCombination + string(1, letter);
                    runCombinationAdder(newCombination, combinations, currentCombinationNode);
                }
            }
        }

    } catch (bad_alloc& ex) {
        cout << "Sizey Wizey: " + to_string(combinations.size());
        ex.what();
    }

    // Using the probabilites (points) for each letter and location to find the best word play
    int highestPoints = -1;
    string bestPlay;

    // At this point all the combinations will be five letter words
    while (!combinations.empty()) {
        string& word = combinations.front().value;
        combinations.pop();

        if (word.length() != 5) {
            throw invalid_argument("Words at this point must be 5 letter wrongs, so something failed!");
        }


        int currentPoints = 0;

        for (int i = 0; i < 5; i++) {
            // Getting the points that were calculated earlier
            currentPoints += probabilities[string(1, word[i]) + to_string(i)];
        }

        if (currentPoints > highestPoints) {
            bestPlay = word;
            highestPoints = currentPoints;
        }
    }
    previousGuess = bestPlay;
    return bestPlay;

}

void WordlePlayer::resetProbabilities() {
    probabilities.clear();
    for (auto character : allLetters) {
        for (int i = 0; i <= 4; i++) {
            // Doing the to_string(i) to convert it into a string
            probabilities.emplace(string(1, character) + to_string(i), 0);
        }
    }
}



void WordlePlayer::update(string result) {
    int index = 0;
    unordered_map<char, int> characterToAmountInWord;
    for (auto character : previousGuess) {
        characterToAmountInWord.emplace(character, 0);
    }
//    cout << "prev guess: " + previousGuess << endl;
//    cout << "Result " + result << endl;

    for (auto character : previousGuess) {
        characterToAmountInWord[character]++;
    }

    for (const auto& resultCharacter : result) {
        char guessCharacter = previousGuess[index];
        int amountOfCharacterInWord = characterToAmountInWord[guessCharacter];

        if (resultCharacter == '-' && amountOfCharacterInWord == 1) {
            makeAllInvalid(guessCharacter);
        }
        else if (resultCharacter == '*' || resultCharacter == '-') {
            // The result and the characters lineup
            validGuesses[string(1, guessCharacter) + to_string(index)] = false;
        }
        else { // Meaning that the correct letter was guessed
            makeCharacterOnlyOption(index, guessCharacter);
        }

        index++;
    }

//    indexToValidCharacters.clear();
//    for (int i = 0; i <= 4; i++) {
//        indexToValidCharacters[i] = vector<char>();
//    }
//    for (const auto& pair : validGuesses) {
//        bool isValidGuess = pair.second;
//
//        if (isValidGuess) {
//            int index2 = stoi(string(1, pair.first[1]));
//            char character = pair.first[0];
//            indexToValidCharacters[index2].emplace_back(character);
//        }
//    }

//    printIndexToValidCharacters();
}

void WordlePlayer::makeAllInvalid(char character) {
    for (int i = 0; i <= 4; i++) {
        validGuesses[string(1, character) + to_string(i)] = false;
    }
}

void WordlePlayer::makeCharacterOnlyOption(int index, char character) {
    for (auto ch : allLetters) {
        validGuesses[string(1, ch) + to_string(index)] = false;
    }
    validGuesses[string(1, character) + to_string(index)] = true; // Updating the value of the actual valid character
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

void WordlePlayer::addWord(const basic_string<char> &word) {
    trie.addWord(word);
}

bool WordlePlayer::hasWord(const basic_string<char> &word) {
    return trie.hasWord(word);
}

void WordlePlayer::runCombinationAdder(string &combination, queue<CombinationObject>& combinations, shared_ptr<Node>& currentCombinationNode) {
    int numberOfLetters = combination.length();
    char& lastLetter = combination[numberOfLetters - 1];
    shared_ptr<Node> nextNode = currentCombinationNode->getNextNode(lastLetter);

    int index = 0;

    if (numberOfLetters == 5) {
        for (const auto& letter : combination) {
            probabilities[string(1,letter) + to_string(index)]++;
            index++;
        }
    }
    combinations.emplace(combination, nextNode);
}

void WordlePlayer::resetValidGuesses() {
    for (auto character : allLetters) {
        for (int i = 0; i <= 4; i++) {
            validGuesses[string(1, character) + to_string(i)] = true;
        }
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



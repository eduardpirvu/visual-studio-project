#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Function to display the hangman figure based on wrong guesses
void displayHangman(int wrongGuesses) {
    cout << "  +---+  " << endl;
    cout << "  |   |  " << endl;
    if (wrongGuesses >= 1) cout << "  O   |  " << endl; else cout << "      |  " << endl;
    if (wrongGuesses >= 3) cout << " /|\\  |  " << endl; else if (wrongGuesses >= 2) cout << " /|   |  " << endl; else cout << "      |  " << endl;
    if (wrongGuesses >= 5) cout << " / \\  |  " << endl; else if (wrongGuesses >= 4) cout << " /    |  " << endl; else cout << "      |  " << endl;
    cout << "      |  " << endl;
    cout << "=========" << endl;
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // List of words
    vector<string> words = {"hangman", "computer", "programming", "cplusplus", "algorithm", "variable", "function", "phone"};

    // Select a random word
    string secretWord = words[rand() % words.size()];

    // Initialize game variables
    string guessedWord(secretWord.length(), '_');
    int maxWrongGuesses = 6;
    int wrongGuesses = 0;
    bool gameWon = false;
    vector<char> wrongLetters;

    // Game loop
    while (wrongGuesses < maxWrongGuesses && !gameWon) {
        // Display current state
        cout << "\nCurrent word: " << guessedWord << endl;
        cout << "Wrong letters: ";
        for (char c : wrongLetters) cout << c << " ";
        cout << endl;
        displayHangman(wrongGuesses);

        // Get player's guess
        char guess;
        cout << "Enter a letter: ";
        cin >> guess;

        // Check if the guess is in the secret word
        bool found = false;
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == guess) {
                guessedWord[i] = guess;
                found = true;
            }
        }

        // If not found, increment wrong guesses
        if (!found) {
            wrongGuesses++;
            wrongLetters.push_back(guess);
            cout << "Wrong guess!" << endl;
        } else {
            cout << "Good guess!" << endl;
        }

        // Check if the word is fully guessed
        if (guessedWord == secretWord) {
            gameWon = true;
        }
    }

    // Display the final result
    displayHangman(wrongGuesses);
    if (gameWon) {
        cout << "Congratulations! You guessed the word: " << secretWord << endl;
    } else {
        cout << "Sorry, you lost. The word was: " << secretWord << endl;
    }

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>

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

// Function to display Easter eggs for special words
void displayEasterEgg(const string& word) {
    if (word == "interstellar") {
        cout << "Easter Egg: Rocket Launch!" << endl;
        cout << "     /\\     " << endl;
        cout << "    /  \\    " << endl;
        cout << "   /    \\   " << endl;
        cout << "  /      \\  " << endl;
        cout << " /        \\ " << endl;
        cout << "|          |" << endl;
        cout << " \\        / " << endl;
        cout << "  \\      /  " << endl;
        cout << "   \\    /   " << endl;
        cout << "    \\  /    " << endl;
        cout << "     \\/     " << endl;
        cout << "    /||\\    " << endl;
        cout << "   //||\\\\   " << endl;
    } else if (word == "robot") {
        cout << "Easter Egg: Robot!" << endl;
        cout << "   /\\_/\\   " << endl;
        cout << "  ( o.o )  " << endl;
        cout << "   > ^ <   " << endl;
        cout << "  /     \\  " << endl;
        cout << " |       | " << endl;
        cout << "  \\     /  " << endl;
        cout << "   \\___/   " << endl;
    } else if (word == "mario") {
        cout << "Easter Egg: Mario Mushroom!" << endl;
        cout << "   ____   " << endl;
        cout << "  /    \\  " << endl;
        cout << " |  ()  | " << endl;
        cout << "  \\____/  " << endl;
        cout << "   ||||   " << endl;
        cout << "   ||||   " << endl;
    } else if (word == "zelda") {
        cout << "Easter Egg: Triforce!" << endl;
        cout << "     /\\     " << endl;
        cout << "    /  \\    " << endl;
        cout << "   /    \\   " << endl;
        cout << "  /      \\  " << endl;
        cout << " /        \\ " << endl;
        cout << " \\        / " << endl;
        cout << "  \\      /  " << endl;
        cout << "   \\    /   " << endl;
        cout << "    \\  /    " << endl;
        cout << "     \\/     " << endl;
    } else if (word == "pacman") {
        cout << "Easter Egg: Pac-Man!" << endl;
        cout << "   .-.   " << endl;
        cout << " .'   '. " << endl;
        cout << "/       \\" << endl;
        cout << "|       |" << endl;
        cout << " \\     / " << endl;
        cout << "  '---'  " << endl;
    } else if (word == "fnaf") {
        cout << "Easter Egg: Freddy Fazbear!" << endl;
        cout << "   .-\"\"\"-.   " << endl;
        cout << "  /       \\  " << endl;
        cout << " |   O O   | " << endl;
        cout << "  \\  ^^^  /  " << endl;
        cout << "   \\_____ /   " << endl;
        cout << "    |   |    " << endl;
        cout << "   /     \\   " << endl;
    } else if (word == "pvz") {
        cout << "Easter Egg: Peashooter!" << endl;
        cout << "     /\\     " << endl;
        cout << "    /  \\    " << endl;
        cout << "   /    \\   " << endl;
        cout << "  /      \\  " << endl;
        cout << " |        | " << endl;
        cout << "  \\      /  " << endl;
        cout << "   \\____/   " << endl;
        cout << "    ||||    " << endl;
    } else if (word == "minecraft") {
        cout << "Easter Egg: Creeper!" << endl;
        cout << "   .-\"\"\"-.   " << endl;
        cout << "  /       \\  " << endl;
        cout << " |  O   O  | " << endl;
        cout << "  \\  ^^^  /  " << endl;
        cout << "   \\_____ /   " << endl;
        cout << "    |   |    " << endl;
        cout << "   /     \\   " << endl;
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    vector<pair<string, vector<vector<string>>>> categories = {
        {"Animals", {
            {"cat", "dog", "goat", "bear", "lion", "fish", "owl", "swan", "mouse", "cow"},
            {"rabbit", "donkey", "giraffe", "penguin", "dolphin", "monkey", "parrot", "otter", "beaver", "turtle"},
            {"elephant", "crocodile", "hedgehog", "kangaroo", "armadillo", "orangutan", "rhinoceros", "butterfly", "woodpecker", "salamander"}
        }},
        {"Fruits", {
            {"apple", "melon", "grape", "pear", "fig", "kiwi", "lemon", "plum", "lime", "berry"},
            {"orange", "banana", "mango", "papaya", "avocado", "nectarine", "guava", "apricot", "coconut", "cranberry"},
            {"pomegranate", "persimmon", "dragonfruit", "elderberry", "boysenberry", "starfruit", "passionfruit", "clementine", "jackfruit", "bloodorange"}
        }},
        {"Countries", {
            {"spain", "italy", "china", "india", "egypt", "nepal", "laos", "cuba", "iran", "chile"},
            {"brazil", "canada", "japan", "germany", "australia", "portugal", "sweden", "finland", "uganda", "poland"},
            {"mozambique", "kyrgyzstan", "liechtenstein", "mauritius", "burkinafaso", "uzbekistan", "venezuela", "swaziland", "czechia", "gabon"}
        }},
        {"Technology", {
            {"mouse", "phone", "modem", "screen", "cable", "router", "drive", "chip", "tablet", "video"},
            {"laptop", "network", "software", "internet", "keyboard", "database", "monitor", "scanner", "graphics", "firewall"},
            {"processor", "algorithm", "robotics", "encryption", "firmware", "interface", "virtualization", "microservice", "nanotechnology", "cybersecurity"}
        }},
        {"Movies", {
            {"jumanji", "rocky", "titanic", "avatar", "aladdin", "casper", "memento", "frozen", "amulet", "psycho"},
            {"inception", "braveheart", "goodfellas", "amelie", "deadpool", "notebook", "skyfall", "findingnemo", "lionking", "cinderella"},
            {"casablanca", "citizenkane", "interstellar", "schindlers", "onceuponatime", "magnificentseven", "twelveangrymen", "amelie", "titanicreview", "groundhog"}
        }},
        {"Video Games", {
            {"tetris", "pong", "mario", "zelda", "pacman", "frogger", "asteroids", "galaga", "centipede", "donkeykong", "fnaf", "pvz"},
            {"sonic", "megaman", "finalfantasy", "streetfighter", "metalgear", "residentevil", "thesims", "worldofwarcraft", "grandtheftauto", "callofduty", "minecraft"},
            {"thelastofus", "reddeadredemption", "thewitcher", "cyberpunk", "godofwar", "assassinscreed", "skyrim", "fallout", "overwatch", "leagueoflegends"}
        }}
    };

    int totalGames = 0;
    int wins = 0;
    int losses = 0;
    int totalScore = 0;
    int highScore = 0;

    cout << "Welcome to Hangman!" << endl;

    bool keepPlaying = true;
    while (keepPlaying) {
        cout << "\033[1;33mPick a difficulty by entering a number:\033[0m" << endl;
        for (size_t i = 0; i < difficulties.size(); ++i) {
            cout << "  \033[1;32m" << (i + 1) << ". " << difficulties[i] << "\033[0m" << endl;
        }

        int difficultyChoice = 0;
        while (difficultyChoice < 1 || difficultyChoice > static_cast<int>(difficulties.size())) {
            cout << "Enter a number between 1 and " << difficulties.size() << ": ";
            if (!(cin >> difficultyChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }

        cout << "\n\033[1;33mChoose a word class by entering a number:\033[0m" << endl;
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << "  \033[1;32m" << (i + 1) << ". " << categories[i].first << "\033[0m" << endl;
        }

        int categoryChoice = 0;
        while (categoryChoice < 1 || categoryChoice > static_cast<int>(categories.size())) {
            cout << "Enter a number between 1 and " << categories.size() << ": ";
            if (!(cin >> categoryChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }

        const vector<string>& words = categories[categoryChoice - 1].second[difficultyChoice - 1];
        string secretWord = words[rand() % words.size()];
        string guessedWord(secretWord.length(), '_');
        int maxWrongGuesses = (difficultyChoice == 1 ? 8 : difficultyChoice == 2 ? 6 : 4);
        int wrongGuesses = 0;
        vector<char> wrongLetters;

        cout << "\nYou selected: " << difficulties[difficultyChoice - 1] << " difficulty, " << categories[categoryChoice - 1].first << "\n" << endl;

        while (wrongGuesses < maxWrongGuesses && guessedWord != secretWord) {
            cout << "Current word: ";
            for (char c : guessedWord) cout << c << ' ';
            cout << endl;

            cout << "Wrong letters: ";
            for (char c : wrongLetters) cout << c << ' ';
            cout << endl;
            displayHangman(wrongGuesses);

            cout << "Enter a letter: ";
            string input;
            cin >> input;
            if (input.empty()) {
                cout << "Please type a letter." << endl;
                continue;
            }

            char guess = static_cast<char>(tolower(input[0]));
            if (!isalpha(static_cast<unsigned char>(guess))) {
                cout << "Please enter a valid letter." << endl;
                continue;
            }

            bool alreadyGuessed = false;
            for (char c : wrongLetters) {
                if (c == guess) {
                    alreadyGuessed = true;
                    break;
                }
            }
            for (char c : guessedWord) {
                if (c == guess) {
                    alreadyGuessed = true;
                    break;
                }
            }

            if (alreadyGuessed) {
                cout << "You already guessed '" << guess << "'. Try a different letter." << endl;
                continue;
            }

            int occurrences = 0;
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == guess) {
                    guessedWord[i] = guess;
                    occurrences++;
                }
            }

            if (occurrences == 0) {
                wrongGuesses++;
                wrongLetters.push_back(guess);
                cout << "Wrong guess!" << endl;
            } else {
                cout << "Good guess!" << endl;
            }

            cout << endl;
        }

        displayHangman(wrongGuesses);
        bool won = false;
        int score = 0;
        if (guessedWord == secretWord) {
            cout << "Congratulations! You guessed the word: " << secretWord << endl;
            won = true;
            score = 10 + (maxWrongGuesses - wrongGuesses) * 2;
            cout << "You earned " << score << " points this round." << endl;
            displayEasterEgg(secretWord);
        } else {
            cout << "Sorry, you lost. The word was: " << secretWord << endl;
            score = 0;
        }

        totalGames++;
        if (won) {
            wins++;
        } else {
            losses++;
        }
        totalScore += score;
        if (score > highScore) {
            highScore = score;
        }

        string answer;
        while (true) {
            cout << "\nWould you like to continue or stop? (c = continue, s = stop): ";
            cin >> answer;
            if (!answer.empty()) {
                char answerChar = static_cast<char>(tolower(answer[0]));
                if (answerChar == 'c') {
                    keepPlaying = true;
                    break;
                }
                if (answerChar == 's') {
                    keepPlaying = false;
                    break;
                }
            }
            cout << "Invalid choice. Enter 'c' to continue or 's' to stop." << endl;
        }

        cout << endl;
    }

    cout << "Game over. High score summary:" << endl;
    cout << "  Games played: " << totalGames << endl;
    cout << "  Wins: " << wins << endl;
    cout << "  Losses: " << losses << endl;
    cout << "  Total score: " << totalScore << endl;
    cout << "  Highest round score: " << highScore << endl;

    return 0;
}

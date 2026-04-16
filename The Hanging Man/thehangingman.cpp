#include <iostream>  // For input/output streams
#include <string>     // For string handling
#include <vector>     // For dynamic arrays (vectors)
#include <set>        // For sets to track unique guessed words
#include <algorithm>  // For algorithms like find
#include <ctime>      // For random number generation
#include <cctype>     // For character functions like tolower
#include <fstream>    // For file input/output
#include <sstream>    // For string stream parsing

using namespace std;

// Structure to hold user account data
struct User {
    string username;
    string password;
    int totalGames = 0;
    int wins = 0;
    int losses = 0;
    int totalScore = 0;
    int highScore = 0;
};

// Function to save user data to file
void saveUserData(const User& user) {
    ifstream infile("accounts.txt");
    vector<string> allLines;
    string line;
    bool userFound = false;

    // Read existing file and update user if exists
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string fileUsername;
                getline(ss, fileUsername, '|');
                
                if (fileUsername == user.username) {
                    // Update existing user
                    allLines.push_back(user.username + "|" + user.password + "|" + 
                                      to_string(user.totalGames) + "|" + 
                                      to_string(user.wins) + "|" + 
                                      to_string(user.losses) + "|" + 
                                      to_string(user.totalScore) + "|" + 
                                      to_string(user.highScore));
                    userFound = true;
                } else {
                    allLines.push_back(line);
                }
            }
        }
        infile.close();
    }

    // If user not found, add new user
    if (!userFound) {
        allLines.push_back(user.username + "|" + user.password + "|" + 
                          to_string(user.totalGames) + "|" + 
                          to_string(user.wins) + "|" + 
                          to_string(user.losses) + "|" + 
                          to_string(user.totalScore) + "|" + 
                          to_string(user.highScore));
    }

    // Write back to file
    ofstream outfile("accounts.txt");
    for (const string& userLine : allLines) {
        outfile << userLine << endl;
    }
    outfile.close();
}

// Function to load user data from file
User loadUserData(const string& username) {
    User user;
    user.username = username;
    ifstream infile("accounts.txt");
    string line;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string fileUsername, password, totalGames, wins, losses, totalScore, highScore;
                
                getline(ss, fileUsername, '|');
                if (fileUsername == username) {
                    getline(ss, password, '|');
                    getline(ss, totalGames, '|');
                    getline(ss, wins, '|');
                    getline(ss, losses, '|');
                    getline(ss, totalScore, '|');
                    getline(ss, highScore, '|');

                    user.password = password;
                    user.totalGames = stoi(totalGames);
                    user.wins = stoi(wins);
                    user.losses = stoi(losses);
                    user.totalScore = stoi(totalScore);
                    user.highScore = stoi(highScore);
                    break;
                }
            }
        }
        infile.close();
    }

    return user;
}

// Function to verify if user exists
bool userExists(const string& username) {
    ifstream infile("accounts.txt");
    string line;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string fileUsername;
                getline(ss, fileUsername, '|');
                if (fileUsername == username) {
                    infile.close();
                    return true;
                }
            }
        }
        infile.close();
    }

    return false;
}

// Function to authenticate user login
bool loginUser(const string& username, const string& password) {
    if (!userExists(username)) {
        return false;
    }

    ifstream infile("accounts.txt");
    string line;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string fileUsername, filePassword;
                getline(ss, fileUsername, '|');
                getline(ss, filePassword, '|');
                
                if (fileUsername == username && filePassword == password) {
                    infile.close();
                    return true;
                }
            }
        }
        infile.close();
    }

    return false;
}

// Function to register a new user
User registerUser() {
    User newUser;
    string username, password, passwordConfirm;

    while (true) {
        cout << "Enter a username: ";
        cin >> username;

        if (userExists(username)) {
            cout << "\033[1;31mUsername already exists. Try a different one.\033[0m" << endl;
            continue;
        }

        if (username.length() < 3) {
            cout << "\033[1;31mUsername must be at least 3 characters long.\033[0m" << endl;
            continue;
        }

        break;
    }

    while (true) {
        cout << "Enter a password (at least 4 characters): ";
        cin >> password;

        if (password.length() < 4) {
            cout << "\033[1;31mPassword must be at least 4 characters long.\033[0m" << endl;
            continue;
        }

        cout << "Confirm your password: ";
        cin >> passwordConfirm;

        if (password != passwordConfirm) {
            cout << "\033[1;31mPasswords don't match. Try again.\033[0m" << endl;
            continue;
        }

        break;
    }

    newUser.username = username;
    newUser.password = password;
    saveUserData(newUser);

    cout << "\n\033[1;32mAccount created successfully!\033[0m" << endl;
    return newUser;
}

// Function to display login/register menu
User authenticateUser() {
    while (true) {
        cout << "\n\033[1;33m=== Hangman - Account System ===\033[0m" << endl;
        cout << "  \033[1;32m1. Login\033[0m" << endl;
        cout << "  \033[1;32m2. Register\033[0m" << endl;
        cout << "Choose an option (1 or 2): ";

        string choice;
        cin >> choice;

        if (choice == "1") {
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (loginUser(username, password)) {
                User user = loadUserData(username);
                cout << "\n\033[1;32mLogin successful! Welcome, " << username << "!\033[0m" << endl;
                return user;
            } else {
                cout << "\033[1;31mInvalid username or password. Try again.\033[0m" << endl;
            }
        } else if (choice == "2") {
            return registerUser();
        } else {
            cout << "\033[1;31mInvalid choice. Enter 1 or 2.\033[0m" << endl;
        }
    }
}

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

    // Authenticate user
    User currentUser = authenticateUser();

    // Initialize game statistics and achievement tracking
    int consecutiveWins = 0;     // Current win streak
    vector<vector<set<string>>> guessedWords(categories.size(), vector<set<string>>(3));  // Tracks guessed words per category/difficulty for achievements

    // Welcome message
    cout << "\n\033[1;32mWelcome to Hangman, " << currentUser.username << "!\033[0m" << endl;

    // Main game loop
    bool keepPlaying = true;
    while (keepPlaying) {
        // Difficulty selection menu
        cout << "\033[1;33mPick a difficulty by entering a number:\033[0m" << endl;
        for (size_t i = 0; i < difficulties.size(); ++i) {
            cout << "  \033[1;32m" << (i + 1) << ". " << difficulties[i] << "\033[0m" << endl;
        }

        // Get valid difficulty choice
        int difficultyChoice = 0;
        while (difficultyChoice < 1 || difficultyChoice > static_cast<int>(difficulties.size())) {
            cout << "Enter a number between 1 and " << difficulties.size() << ": ";
            if (!(cin >> difficultyChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }

        // Category selection menu
        cout << "\n\033[1;33mChoose a word class by entering a number:\033[0m" << endl;
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << "  \033[1;32m" << (i + 1) << ". " << categories[i].first << "\033[0m" << endl;
        }

        // Get valid category choice
        int categoryChoice = 0;
        while (categoryChoice < 1 || categoryChoice > static_cast<int>(categories.size())) {
            cout << "Enter a number between 1 and " << categories.size() << ": ";
            if (!(cin >> categoryChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }

        // Select random word from chosen category and difficulty
        const vector<string>& words = categories[categoryChoice - 1].second[difficultyChoice - 1];
        string secretWord = words[rand() % words.size()];
        string guessedWord(secretWord.length(), '_');  // Initialize guessed word with underscores
        int maxWrongGuesses = (difficultyChoice == 1 ? 8 : difficultyChoice == 2 ? 6 : 4);  // Set max guesses based on difficulty
        int wrongGuesses = 0;
        vector<char> wrongLetters;  // List of incorrect guesses

        // Confirm selection
        cout << "\nYou selected: " << difficulties[difficultyChoice - 1] << " difficulty, " << categories[categoryChoice - 1].first << "\n" << endl;

        // Game loop for guessing
        while (wrongGuesses < maxWrongGuesses && guessedWord != secretWord) {
            // Display current game state
            cout << "Current word: ";
            for (char c : guessedWord) cout << c << ' ';
            cout << endl;

            cout << "Wrong letters: ";
            for (char c : wrongLetters) cout << c << ' ';
            cout << endl;
            displayHangman(wrongGuesses);

            // Get player's guess
            cout << "Enter a letter: ";
            string input;
            cin >> input;
            if (input.empty()) {
                cout << "Please type a letter." << endl;
                continue;
            }

            // Normalize guess to lowercase
            char guess = static_cast<char>(tolower(input[0]));
            
            // Validate that the input is a letter (restrict to alphabetic characters only)
            // isalpha() checks if the character is a letter (A-Z, a-z)
            // This prevents players from entering numbers, symbols, or special characters
            if (!isalpha(static_cast<unsigned char>(guess))) {
                cout << "Please enter a valid letter. No numbers or symbols allowed." << endl;
                continue;
            }

            // Check if already guessed
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

            // Check guess against secret word
            int occurrences = 0;
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == guess) {
                    guessedWord[i] = guess;
                    occurrences++;
                }
            }

            // Update game state
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

            consecutiveWins++;
            guessedWords[categoryChoice - 1][difficultyChoice - 1].insert(secretWord);

            // Check achievements
            if (consecutiveWins == 1) {
                cout << "\033[1;36mAchievement Unlocked: First Victory!\033[0m" << endl;
            } else if (consecutiveWins == 5) {
                cout << "\033[1;36mAchievement Unlocked: Streak Master (5 wins in a row)!\033[0m" << endl;
            } else if (consecutiveWins == 10) {
                cout << "\033[1;36mAchievement Unlocked: Legendary Streak (10 wins in a row)!\033[0m" << endl;
            }

            const vector<string>& words = categories[categoryChoice - 1].second[difficultyChoice - 1];
            if (guessedWords[categoryChoice - 1][difficultyChoice - 1].size() == words.size()) {
                cout << "\033[1;36mAchievement Unlocked: Master of " << categories[categoryChoice - 1].first << " (" << difficulties[difficultyChoice - 1] << ")!\033[0m" << endl;
            }
        } else {
            cout << "Sorry, you lost. The word was: " << secretWord << endl;
            score = 0;
            consecutiveWins = 0;
        }

        // Update user statistics
        currentUser.totalGames++;
        if (won) {
            currentUser.wins++;
        } else {
            currentUser.losses++;
        }
        currentUser.totalScore += score;
        if (score > currentUser.highScore) {
            currentUser.highScore = score;
        }

        // Save current user stats
        saveUserData(currentUser);

        // Ask to continue or stop
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

    // Final statistics
    cout << "\n\033[1;33mGame over. High score summary for " << currentUser.username << ":\033[0m" << endl;
    cout << "  Games played: " << currentUser.totalGames << endl;
    cout << "  Wins: " << currentUser.wins << endl;
    cout << "  Losses: " << currentUser.losses << endl;
    cout << "  Total score: " << currentUser.totalScore << endl;
    cout << "  Highest round score: " << currentUser.highScore << endl;

    // Save final stats
    saveUserData(currentUser);
    cout << "\n\033[1;32mYour stats have been saved. Thanks for playing!\033[0m" << endl;

    return 0;
}

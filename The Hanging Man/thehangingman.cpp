#include <iostream>  // For input/output streams
#include <string>     // For string handling
#include <vector>     // For dynamic arrays (vectors)
#include <set>        // For sets to track unique guessed words
#include <algorithm>  // For algorithms like find
#include <map>        // For organizing words by category and difficulty
#include <ctime>      // For random number generation
#include <cctype>     // For character functions like tolower
#include <fstream>    // For file input/output
#include <sstream>    // For string stream parsing
#include <chrono>     // For timer mode
#include <conio.h>    // For hidden input with getch()

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
    int bestStreak = 0;
    int firstVictory = 0;           // Achievement: 1st win
    int streakMaster = 0;            // Achievement: 5 consecutive wins
    int legendaryStreak = 0;         // Achievement: 10 consecutive wins
    map<string, map<int, bool>> categoryMastery;  // Achievement: mastered category/difficulty
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
                    // Update existing user with all stats including achievements
                    allLines.push_back(user.username + "|" + user.password + "|" + 
                                      to_string(user.totalGames) + "|" + 
                                      to_string(user.wins) + "|" + 
                                      to_string(user.losses) + "|" + 
                                      to_string(user.totalScore) + "|" + 
                                      to_string(user.highScore) + "|" + 
                                      to_string(user.bestStreak) + "|" +
                                      to_string(user.firstVictory) + "|" +
                                      to_string(user.streakMaster) + "|" +
                                      to_string(user.legendaryStreak));
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
                          to_string(user.highScore) + "|" + 
                          to_string(user.bestStreak) + "|" +
                          to_string(user.firstVictory) + "|" +
                          to_string(user.streakMaster) + "|" +
                          to_string(user.legendaryStreak));
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
                string fileUsername, password, totalGames, wins, losses, totalScore, highScore, bestStreak;
                string firstVictory = "0", streakMaster = "0", legendaryStreak = "0";
                
                getline(ss, fileUsername, '|');
                if (fileUsername == username) {
                    getline(ss, password, '|');
                    getline(ss, totalGames, '|');
                    getline(ss, wins, '|');
                    getline(ss, losses, '|');
                    getline(ss, totalScore, '|');
                    getline(ss, highScore, '|');
                    getline(ss, bestStreak, '|');

                    user.password = password;
                    user.totalGames = stoi(totalGames);
                    user.wins = stoi(wins);
                    user.losses = stoi(losses);
                    user.totalScore = stoi(totalScore);
                    user.highScore = stoi(highScore);
                    if (!bestStreak.empty()) {
                        user.bestStreak = stoi(bestStreak);
                    }
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
                cout << "Your best winning streak: " << user.bestStreak << "\n" << endl;
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

// Structure to hold easter egg data
struct EasterEgg {
    string word;
    int rarity;  // 0-100 percentage, 100 = always show, <100 = random chance
    int difficulty;  // 1-3, 0 means all difficulties
    string title;
    vector<string> asciiArt;
};

map<string, vector<EasterEgg>> easterEggMap;

map<string, vector<EasterEgg>> loadEasterEggsFromFile(const string& filename) {
    map<string, vector<EasterEgg>> result;
    
    // Try multiple possible paths for the file
    vector<string> possiblePaths = {
        filename,                          // Current directory
        "../" + filename,                  // Parent directory
        "../../" + filename,               // Grandparent directory
        "./" + filename                    // Explicit current directory
    };
    
    ifstream infile;
    string successPath;
    
    for (const string& path : possiblePaths) {
        infile.open(path);
        if (infile.is_open()) {
            successPath = path;
            break;
        }
    }

    if (!infile.is_open()) {
        cerr << "\033[1;33mWarning: Could not open " << filename << " from any location. Easter eggs disabled.\033[0m" << endl;
        return result;
    }

    cout << "\033[1;32m✓ Found " << filename << " at: " << successPath << "\033[0m" << endl;

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        
        // Format: word|rarity|difficulty|title::line1::line2::line3
        size_t pipePos1 = line.find('|');
        size_t pipePos2 = line.find('|', pipePos1 + 1);
        size_t pipePos3 = line.find('|', pipePos2 + 1);
        
        if (pipePos1 == string::npos || pipePos2 == string::npos || pipePos3 == string::npos) {
            continue;
        }
        
        string word = line.substr(0, pipePos1);
        string rarityStr = line.substr(pipePos1 + 1, pipePos2 - pipePos1 - 1);
        string diffStr = line.substr(pipePos2 + 1, pipePos3 - pipePos2 - 1);
        string artSection = line.substr(pipePos3 + 1);
        
        // Split art section into title and ASCII art using :: separator
        size_t artSeparator = artSection.find("::");
        if (artSeparator == string::npos) continue;
        
        string title = artSection.substr(0, artSeparator);
        string artLines = artSection.substr(artSeparator + 2);
        
        vector<string> asciiLines;
        size_t pos = 0;
        while (pos < artLines.size()) {
            size_t nextSep = artLines.find("::", pos);
            if (nextSep == string::npos) {
                asciiLines.push_back(artLines.substr(pos));
                break;
            }
            asciiLines.push_back(artLines.substr(pos, nextSep - pos));
            pos = nextSep + 2;
        }
        
        try {
            int rarity = stoi(rarityStr);
            int difficulty = stoi(diffStr);
            
            EasterEgg egg;
            egg.word = word;
            egg.rarity = rarity;
            egg.difficulty = difficulty;
            egg.title = title;
            egg.asciiArt = asciiLines;
            
            result[word].push_back(egg);
        } catch (...) {
            continue;
        }
    }
    infile.close();
    
    cout << "\033[1;32m✓ Loaded " << result.size() << " easter egg entries\033[0m" << endl;
    return result;
}

bool shouldShowEasterEgg(int rarity) {
    if (rarity >= 100) return true;
    int random = rand() % 100;
    return random < rarity;
}

void displayEasterEgg(const string& word, int difficulty = 1) {
    if (easterEggMap.find(word) != easterEggMap.end()) {
        vector<EasterEgg>& eggs = easterEggMap[word];
        
        vector<EasterEgg> validEggs;
        for (EasterEgg& egg : eggs) {
            if ((egg.difficulty == 0 || egg.difficulty == difficulty) && shouldShowEasterEgg(egg.rarity)) {
                validEggs.push_back(egg);
            }
        }
        
        if (!validEggs.empty()) {
            EasterEgg& selectedEgg = validEggs[rand() % validEggs.size()];
            cout << "\033[1;35m" << selectedEgg.title << "\033[0m" << endl;
            for (const string& line : selectedEgg.asciiArt) {
                cout << line << endl;
            }
        }
    }
}

// Old function kept for compatibility (removed hardcoded eggs)
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
struct RoundOutcome {
    bool guessed = false;
    bool timedOut = false;
    int wrongGuesses = 0;
    int guesserScore = 0;
    int setterScore = 0;
};

string getHiddenWordInput(const string& prompt) {
    cout << prompt;
    string result;
    while (true) {
        int ch = getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        if (ch == '\b') {
            if (!result.empty()) {
                result.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        if (isprint(static_cast<unsigned char>(ch))) {
            result.push_back(static_cast<char>(ch));
            cout << '*';
        }
    }
    cout << endl;
    return result;
}

int calculateWordBonus(const string& secretWord) {
    set<char> uniqueLetters;
    for (char c : secretWord) {
        uniqueLetters.insert(c);
    }
    int lengthBonus = max(0, static_cast<int>(secretWord.size()) - 5);
    int uniqueBonus = max(0, static_cast<int>(uniqueLetters.size()) - 4);
    return lengthBonus + uniqueBonus;
}

bool isFairWord(const string& word) {
    if (word.size() < 4) {
        return false;
    }
    set<char> uniqueLetters;
    for (char c : word) {
        uniqueLetters.insert(c);
    }
    return uniqueLetters.size() >= 3;
}

RoundOutcome playRound(const string& secretWord, int maxWrongGuesses, int availableHints, int totalTimeAllowed, bool timerMode) {
    string guessedWord(secretWord.length(), '_');
    vector<char> wrongLetters;
    auto startTime = chrono::steady_clock::now();
    RoundOutcome result;
    result.timedOut = false;
    result.guessed = false;
    result.wrongGuesses = 0;

    while (result.wrongGuesses < maxWrongGuesses && guessedWord != secretWord) {
        if (timerMode) {
            auto elapsed = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
            if (elapsed >= totalTimeAllowed) {
                result.timedOut = true;
                break;
            }
            cout << "Time left: " << (totalTimeAllowed - elapsed) << " seconds" << endl;
        }

        cout << "Current word: ";
        for (char c : guessedWord) cout << c << ' ';
        cout << endl;

        cout << "Wrong letters: ";
        for (char c : wrongLetters) cout << c << ' ';
        cout << endl;
        displayHangman(result.wrongGuesses);

        cout << "Enter a letter or type 'hint' to reveal one letter. Hints left: " << availableHints << ": ";
        string input;
        cin >> input;
        if (input.empty()) {
            cout << "Please type a letter or 'hint'." << endl;
            continue;
        }

        string lowerInput = input;
        for (char& c : lowerInput) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (lowerInput == "hint") {
            if (availableHints <= 0) {
                cout << "No hints left. Please enter a letter." << endl;
                continue;
            }
            vector<int> hiddenPositions;
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (guessedWord[i] == '_') {
                    hiddenPositions.push_back(static_cast<int>(i));
                }
            }
            if (hiddenPositions.empty()) {
                cout << "All letters are already revealed." << endl;
                continue;
            }
            int revealIndex = hiddenPositions[rand() % hiddenPositions.size()];
            char revealLetter = secretWord[revealIndex];
            int revealedCount = 0;
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == revealLetter && guessedWord[i] == '_') {
                    guessedWord[i] = revealLetter;
                    revealedCount++;
                }
            }
            availableHints--;
            cout << "Hint used! Revealed letter '" << revealLetter << "' (" << revealedCount << " position" << (revealedCount != 1 ? "s" : "") << "). Hints left: " << availableHints << "." << endl;
            continue;
        }

        if (lowerInput.length() != 1) {
            cout << "Please enter a single letter or type 'hint'." << endl;
            continue;
        }

        char guess = static_cast<char>(tolower(lowerInput[0]));
        if (!isalpha(static_cast<unsigned char>(guess))) {
            cout << "Please enter a valid letter. No numbers or symbols allowed." << endl;
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
            result.wrongGuesses++;
            wrongLetters.push_back(guess);
            cout << "Wrong guess!" << endl;
        } else {
            cout << "Good guess!" << endl;
        }
        cout << endl;
    }

    if (timerMode && !result.timedOut) {
        auto elapsed = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
        if (elapsed >= totalTimeAllowed) {
            result.timedOut = true;
        }
    }

    if (!result.timedOut && guessedWord == secretWord) {
        result.guessed = true;
    }

    int bonus = calculateWordBonus(secretWord);
    if (result.guessed) {
        int guesserBase = 10 + (maxWrongGuesses - result.wrongGuesses) * 2;
        result.guesserScore = guesserBase + bonus;
        result.setterScore = max(1, bonus);
    } else {
        result.guesserScore = 0;
        result.setterScore = 10 + bonus;
    }

    if (!result.guessed) {
        cout << "The word was: " << secretWord << endl;
    }
    return result;
}

int getDifficultyFromLength(const string& secretWord) {
    if (secretWord.length() <= 5) return 1;
    if (secretWord.length() <= 7) return 2;
    return 3;
}

int getMaxWrongGuesses(int difficultyChoice) {
    return (difficultyChoice == 1 ? 8 : difficultyChoice == 2 ? 6 : 4);
}

int getAvailableHints(int difficultyChoice) {
    return (difficultyChoice == 3 ? 1 : 2);
}

int getTimerForDifficulty(int difficultyChoice) {
    return (difficultyChoice == 1 ? 90 : difficultyChoice == 2 ? 60 : 45);
}

int getPlayerRoundScore(const RoundOutcome& outcome, bool guesserWon) {
    return guesserWon ? outcome.guesserScore : outcome.setterScore;
}

int getSetterRoundScore(const RoundOutcome& outcome, bool guesserWon) {
    // Setter scores when guesser FAILS (didn't guess the word)
    return !guesserWon ? outcome.setterScore : 0;
}

vector<pair<string, vector<vector<string>>>> loadWordsFromFile(const string& filename) {
    map<string, map<int, vector<string>>> wordMap;
    
    // Try multiple possible paths for the file
    vector<string> possiblePaths = {
        filename,                          // Current directory
        "../" + filename,                  // Parent directory
        "../../" + filename,               // Grandparent directory
        "./" + filename                    // Explicit current directory
    };
    
    ifstream infile;
    string successPath;
    
    for (const string& path : possiblePaths) {
        infile.open(path);
        if (infile.is_open()) {
            successPath = path;
            break;
        }
    }
    
    int lineNumber = 0;
    int validLines = 0;
    int invalidLines = 0;
    
    if (!infile.is_open()) {
        cerr << "\033[1;31mERROR: Could not open " << filename << " from any location.\033[0m" << endl;
        cerr << "Searched: current dir, parent dir, grandparent dir" << endl;
        exit(1);
    }

    cout << "\033[1;32m✓ Found " << filename << " at: " << successPath << "\033[0m" << endl;

    string line;
    while (getline(infile, line)) {
        lineNumber++;
        if (line.empty()) continue;
        
        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);
        
        if (firstComma == string::npos || secondComma == string::npos) {
            invalidLines++;
            cerr << "\033[1;33mWarning: Line " << lineNumber << " has invalid format (not enough commas). Skipping...\033[0m" << endl;
            continue;
        }
        
        string category = line.substr(0, firstComma);
        string diffStr = line.substr(firstComma + 1, secondComma - firstComma - 1);
        string word = line.substr(secondComma + 1);
        
        // Trim whitespace
        if (!category.empty() && category.back() == ' ') category.pop_back();
        if (!diffStr.empty() && diffStr[0] == ' ') diffStr = diffStr.substr(1);
        if (!word.empty() && word[0] == ' ') word = word.substr(1);
        
        if (category.empty() || diffStr.empty() || word.empty()) {
            invalidLines++;
            cerr << "\033[1;33mWarning: Line " << lineNumber << " contains empty fields. Skipping...\033[0m" << endl;
            continue;
        }
        
        try {
            int difficulty = stoi(diffStr);
            if (difficulty < 1 || difficulty > 3) {
                invalidLines++;
                cerr << "\033[1;33mWarning: Line " << lineNumber << " has invalid difficulty '" << difficulty << "' (must be 1-3). Skipping...\033[0m" << endl;
                continue;
            }
            wordMap[category][difficulty].push_back(word);
            validLines++;
        } catch (...) {
            invalidLines++;
            cerr << "\033[1;33mWarning: Line " << lineNumber << " has non-numeric difficulty '" << diffStr << "'. Skipping...\033[0m" << endl;
            continue;
        }
    }
    infile.close();

    vector<pair<string, vector<vector<string>>>> result;
    
    if (validLines == 0) {
        cerr << "\033[1;31mERROR: No valid words loaded from " << filename << ". File appears to be corrupted or empty.\033[0m" << endl;
        exit(1);
    }
    
    cout << "\033[1;32m✓ Loaded " << validLines << " words from " << filename << endl;
    if (invalidLines > 0) {
        cout << "\033[1;33m⚠ Skipped " << invalidLines << " invalid lines\033[0m" << endl;
    }

    if (wordMap.empty()) {
        cerr << "\033[1;31mERROR: No word categories found in " << filename << ".\033[0m" << endl;
        exit(1);
    }
    
    // Extract categories from file dynamically instead of hardcoding
    for (auto& catPair : wordMap) {
        const string& category = catPair.first;
        auto& diffMap = catPair.second;
        
        vector<vector<string>> difficulties(3);
        for (int d = 1; d <= 3; ++d) {
            if (diffMap.count(d)) {
                difficulties[d - 1] = diffMap[d];
            } else {
                // Fallback: use words from adjacent difficulty
                if (d == 1 && diffMap.count(2)) {
                    difficulties[d - 1] = diffMap[2];
                    cout << "\033[1;33m⚠ Category '" << category << "' missing difficulty 1, using difficulty 2 as fallback\033[0m" << endl;
                } else if (d == 3 && diffMap.count(2)) {
                    difficulties[d - 1] = diffMap[2];
                    cout << "\033[1;33m⚠ Category '" << category << "' missing difficulty 3, using difficulty 2 as fallback\033[0m" << endl;
                } else if (d == 2 && diffMap.count(1)) {
                    difficulties[d - 1] = diffMap[1];
                    cout << "\033[1;33m⚠ Category '" << category << "' missing difficulty 2, using difficulty 1 as fallback\033[0m" << endl;
                }
            }
        }
        
        // Only add category if it has at least some words
        bool hasWords = false;
        for (const auto& diffVec : difficulties) {
            if (!diffVec.empty()) {
                hasWords = true;
                break;
            }
        }
        
        if (hasWords) {
            result.push_back({category, difficulties});
        }
    }
    
    if (result.empty()) {
        cerr << "\033[1;31mERROR: All categories are empty after fallback attempts.\033[0m" << endl;
        exit(1);
    }
    
    return result;
}

// Display main menu and get game mode selection
int showMainMenu() {
    cout << "\n\033[1;33mSelect a game mode:\033[0m" << endl;
    cout << "  \033[1;32m1. Default\033[0m - Classic hangman mode" << endl;
    cout << "  \033[1;32m2. Timer mode\033[0m - Race against the clock" << endl;
    cout << "  \033[1;32m3. Multiplayer mode\033[0m - Compete with another player" << endl;
    cout << "  \033[1;32m4. Progressive difficulty\033[0m - Difficulty increases with wins" << endl;

    int gameMode = 0;
    while (gameMode < 1 || gameMode > 4) {
        cout << "Choose a mode by entering 1-4: ";
        if (!(cin >> gameMode)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }
    }
    return gameMode;
}

// Run single player game modes (default, timer, progressive)
void runSinglePlayer(
    User& currentUser,
    const vector<pair<string, vector<vector<string>>>>& categories,
    const vector<string>& difficulties,
    int gameMode,
    int& consecutiveWins,
    int& progressiveDifficultyLevel,
    vector<vector<set<string>>>& guessedWords
) {
    int difficultyChoice = 0;
    int categoryChoice = 0;
    bool timerMode = (gameMode == 2);
    bool progressiveMode = (gameMode == 4);
    int totalTimeAllowed = 0;
    
    // Select difficulty
    if (!progressiveMode) {
        cout << "\033[1;33mPick a difficulty by entering a number:\033[0m" << endl;
        for (size_t i = 0; i < difficulties.size(); ++i) {
            cout << "  \033[1;32m" << (i + 1) << ". " << difficulties[i] << "\033[0m" << endl;
        }

        while (difficultyChoice < 1 || difficultyChoice > static_cast<int>(difficulties.size())) {
            cout << "Enter a number between 1 and " << difficulties.size() << ": ";
            if (!(cin >> difficultyChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }
    } else {
        difficultyChoice = progressiveDifficultyLevel + 1;
        cout << "\n\033[1;32mProgressive difficulty mode: current difficulty is " << difficulties[progressiveDifficultyLevel] << ".\033[0m" << endl;
    }

    if (timerMode) {
        totalTimeAllowed = (difficultyChoice == 1 ? 90 : difficultyChoice == 2 ? 60 : 45);
        cout << "\n\033[1;32mTimer mode active: you have " << totalTimeAllowed << " seconds to finish this round.\033[0m" << endl;
    }

    // Select category
    cout << "\n\033[1;33mChoose a word class by entering a number:\033[0m" << endl;
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << "  \033[1;32m" << (i + 1) << ". " << categories[i].first << "\033[0m" << endl;
    }

    while (categoryChoice < 1 || categoryChoice > static_cast<int>(categories.size())) {
        cout << "Enter a number between 1 and " << categories.size() << ": ";
        if (!(cin >> categoryChoice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
        }
    }

    // Get word and check if category has words for difficulty
    const vector<string>& categoryWords = categories[categoryChoice - 1].second[difficultyChoice - 1];
    if (categoryWords.empty()) {
        cout << "\033[1;31mERROR: No words available for selected category and difficulty.\\033[0m" << endl;
        return;
    }

    string secretWord = categoryWords[rand() % categoryWords.size()];
    cout << "\nYou selected: " << difficulties[difficultyChoice - 1] << " difficulty, " << categories[categoryChoice - 1].first << "\n" << endl;

    int maxWrongGuesses = getMaxWrongGuesses(difficultyChoice);
    int availableHints = getAvailableHints(difficultyChoice);

    RoundOutcome outcome = playRound(secretWord, maxWrongGuesses, availableHints, totalTimeAllowed, timerMode);

    bool won = (outcome.guessed && !outcome.timedOut);
    int score = 0;

    if (outcome.timedOut) {
        cout << "Time's up! You ran out of time. The word was: " << secretWord << endl;
        score = 0;
        consecutiveWins = 0;
    } else if (won) {
        cout << "Congratulations! You guessed the word: " << secretWord << endl;
        score = outcome.guesserScore;
        cout << "You earned " << score << " points this round." << endl;
        displayEasterEgg(secretWord, difficultyChoice);

        consecutiveWins++;
        if (progressiveMode && progressiveDifficultyLevel < 2) {
            progressiveDifficultyLevel++;
        }
        guessedWords[categoryChoice - 1][difficultyChoice - 1].insert(secretWord);

        // Check and unlock achievements
        if (consecutiveWins == 1 && !currentUser.firstVictory) {
            currentUser.firstVictory = 1;
            cout << "\033[1;36mAchievement Unlocked: First Victory!\033[0m" << endl;
        } else if (consecutiveWins == 5 && !currentUser.streakMaster) {
            currentUser.streakMaster = 1;
            cout << "\033[1;36mAchievement Unlocked: Streak Master (5 wins in a row)!\033[0m" << endl;
        } else if (consecutiveWins == 10 && !currentUser.legendaryStreak) {
            currentUser.legendaryStreak = 1;
            cout << "\033[1;36mAchievement Unlocked: Legendary Streak (10 wins in a row)!\033[0m" << endl;
        }

        // Category mastery achievement
        if (guessedWords[categoryChoice - 1][difficultyChoice - 1].size() == categoryWords.size()) {
            currentUser.categoryMastery[categories[categoryChoice - 1].first][difficultyChoice] = true;
            cout << "\033[1;36mAchievement Unlocked: Master of " << categories[categoryChoice - 1].first << " (" << difficulties[difficultyChoice - 1] << ")!\033[0m" << endl;
        }
    } else {
        cout << "Sorry, you lost. The word was: " << secretWord << endl;
        score = 0;
        consecutiveWins = 0;
        if (progressiveMode) {
            progressiveDifficultyLevel = 0;
        }
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
    if (consecutiveWins > currentUser.bestStreak) {
        currentUser.bestStreak = consecutiveWins;
    }

    saveUserData(currentUser);
}

// Run multiplayer best-of-3 game
void runMultiplayer() {
    cout << "\n\033[1;33mMultiplayer mode: both players must log in separately.\033[0m" << endl;
    cout << "\n\033[1;32mPlayer 1 login:\033[0m" << endl;
    User player1 = authenticateUser();
    cout << "\n\033[1;32mPlayer 2 login:\033[0m" << endl;
    User player2;
    while (true) {
        player2 = authenticateUser();
        if (player2.username != player1.username) {
            break;
        }
        cout << "\033[1;31mPlayer 2 must use a different username than Player 1.\033[0m" << endl;
    }

    cout << "\n\033[1;32mBest of 3 rounds begins!\033[0m" << endl;
    int player1RoundWins = 0;
    int player2RoundWins = 0;
    int player1TotalScore = 0;
    int player2TotalScore = 0;
    int player1CurrentStreak = 0;
    int player2CurrentStreak = 0;

    for (int roundNumber = 1; roundNumber <= 3 && player1RoundWins < 2 && player2RoundWins < 2; ++roundNumber) {
        bool player1Setter = (roundNumber % 2 == 1);
        User* setter = player1Setter ? &player1 : &player2;
        User* guesser = player1Setter ? &player2 : &player1;

        cout << "\n\033[1;33mRound " << roundNumber << ": " << setter->username << " chooses the word, " << guesser->username << " guesses.\033[0m" << endl;
        
        string roundWord;
        while (true) {
            roundWord = getHiddenWordInput(setter->username + ", enter a secret word (letters only): ");
            bool valid = !roundWord.empty();
            for (char c : roundWord) {
                if (!isalpha(static_cast<unsigned char>(c))) {
                    valid = false;
                    break;
                }
            }
            for (char& c : roundWord) {
                c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }
            if (!valid || !isFairWord(roundWord)) {
                cout << "\033[1;31mFair word rule: please use at least 4 letters and at least 3 unique characters.\033[0m" << endl;
                continue;
            }
            break;
        }

        int roundDifficulty = getDifficultyFromLength(roundWord);
        int roundMaxWrong = getMaxWrongGuesses(roundDifficulty);
        int roundHints = getAvailableHints(roundDifficulty);
        cout << "\033[1;32m" << guesser->username << ", you have " << roundMaxWrong << " wrong guesses allowed this round.\033[0m" << endl;

        RoundOutcome outcome = playRound(roundWord, roundMaxWrong, roundHints, 0, false);

        int guesserScore = outcome.guesserScore;
        int setterScore = getSetterRoundScore(outcome, outcome.guessed);
        
        if (player1Setter) {
            player1TotalScore += setterScore;
            player2TotalScore += guesserScore;
        } else {
            player2TotalScore += setterScore;
            player1TotalScore += guesserScore;
        }

        if (outcome.guessed) {
            cout << "\033[1;32m" << guesser->username << " wins Round " << roundNumber << "!\033[0m" << endl;
            if (player1Setter) {
                player2RoundWins++;
                player2CurrentStreak++;
                player1CurrentStreak = 0;
            } else {
                player1RoundWins++;
                player1CurrentStreak++;
                player2CurrentStreak = 0;
            }
        } else {
            cout << "\033[1;31m" << setter->username << " wins Round " << roundNumber << "!\033[0m" << endl;
            if (player1Setter) {
                player1RoundWins++;
                player1CurrentStreak++;
                player2CurrentStreak = 0;
            } else {
                player2RoundWins++;
                player2CurrentStreak++;
                player1CurrentStreak = 0;
            }
        }

        cout << "Round scores: " << player1.username << " " << player1RoundWins << "-" << player2RoundWins << ", " 
             << player1.username << " total " << player1TotalScore << ", " << player2.username << " total " << player2TotalScore << ".\n";
    }

    bool player1MatchWinner = false;
    if (player1RoundWins > player2RoundWins || (player1RoundWins == player2RoundWins && player1TotalScore > player2TotalScore)) {
        player1MatchWinner = true;
    }
    
    cout << "\n\033[1;36mMatch result: ";
    if (player1MatchWinner) {
        cout << player1.username << " wins the match!\033[0m" << endl;
    } else if (player2RoundWins > player1RoundWins || (player1RoundWins == player2RoundWins && player2TotalScore > player1TotalScore)) {
        cout << player2.username << " wins the match!\033[0m" << endl;
    } else {
        cout << "The match is a tie!\033[0m" << endl;
    }

    player1.totalGames += player1RoundWins + player2RoundWins;
    player2.totalGames += player1RoundWins + player2RoundWins;
    player1.wins += player1RoundWins;
    player1.losses += player2RoundWins;
    player2.wins += player2RoundWins;
    player2.losses += player1RoundWins;
    player1.totalScore += player1TotalScore;
    player2.totalScore += player2TotalScore;
    player1.highScore = max(player1.highScore, player1TotalScore);
    player2.highScore = max(player2.highScore, player2TotalScore);
    player1.bestStreak = max(player1.bestStreak, player1CurrentStreak);
    player2.bestStreak = max(player2.bestStreak, player2CurrentStreak);

    saveUserData(player1);
    saveUserData(player2);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    
    // Load words from external file (required)
    vector<pair<string, vector<vector<string>>>> categories = loadWordsFromFile("words.txt");

    // Load easter eggs from external file
    easterEggMap = loadEasterEggsFromFile("easter_eggs.txt");

    // Authenticate user
    User currentUser = authenticateUser();

    // Initialize game statistics and achievement tracking
    int consecutiveWins = 0;     
    int progressiveDifficultyLevel = 0;
    vector<vector<set<string>>> guessedWords(categories.size(), vector<set<string>>(3));
    
    cout << "\n\033[1;32mWelcome to Hangman, " << currentUser.username << "!\033[0m" << endl;

    // Main game loop
    bool keepPlaying = true;
    while (keepPlaying) {
        int gameMode = showMainMenu();

        if (gameMode == 3) {
            // Multiplayer mode
            runMultiplayer();
        } else {
            // Single player modes
            runSinglePlayer(currentUser, categories, difficulties, gameMode, 
                           consecutiveWins, progressiveDifficultyLevel, guessedWords);
        }

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

    // Reload current user data to get any updates from multiplayer sessions
    currentUser = loadUserData(currentUser.username);

    // Final statistics
    cout << "\n\033[1;33mGame over. High score summary for " << currentUser.username << ":\033[0m" << endl;
    cout << "  Games played: " << currentUser.totalGames << endl;
    cout << "  Wins: " << currentUser.wins << endl;
    cout << "  Losses: " << currentUser.losses << endl;
    cout << "  Total score: " << currentUser.totalScore << endl;
    cout << "  Highest round score: " << currentUser.highScore << endl;
    cout << "  Best winning streak: " << currentUser.bestStreak << endl;

    // Save final stats
    saveUserData(currentUser);
    cout << "\n\033[1;32mYour stats have been saved. Thanks for playing!\033[0m" << endl;

    return 0;
}

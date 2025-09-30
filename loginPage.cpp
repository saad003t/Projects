#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

class User {
private:
    string username;
    string email;
    string password;
    const string FILENAME = "loginData.txt";
    const char DELIMITER = '*';

    bool isValidEmail(const string& email) {
        return email.find('@') != string::npos && email.find(".com") != string::npos;
    }

    bool findAccount(const string& searchUsername, const string& searchEmail = "") {
        ifstream file(FILENAME);
        string line;
        
        while (getline(file, line)) {
            size_t pos1 = line.find(DELIMITER);
            size_t pos2 = line.find(DELIMITER, pos1 + 1);
            
            string fileUsername = line.substr(0, pos1);
            string fileEmail = line.substr(pos1 + 1, pos2 - pos1 - 1);
            
            if (fileUsername == searchUsername && (searchEmail.empty() || fileEmail == searchEmail)) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

public:
    void signUp() {
        clearScreen();
        cout << "\n=== Sign Up ===\n";

        bool validUsername = false;
        while (!validUsername) {
            cout << "\nEnter Username: ";
            getline(cin, username);
            clearScreen();
            
            if (username.empty()) {
                cout << "Username cannot be empty!\n";
                continue;
            }
            
            if (findAccount(username)) {
                cout << "Username already exists! Please choose another.\n";
                continue;
            }
            
            validUsername = true;
        }

        bool validEmail = false;
        while (!validEmail) {
            cout << "\n=== Sign Up ===\n";
            cout << "Username: " << username << endl;
            cout << "Enter Email Address: ";
            getline(cin, email);
            clearScreen();
            
            if (!isValidEmail(email)) {
                cout << "\nInvalid email format! Email must contain '@' and '.com'\n";
                continue;
            }
            validEmail = true;
        }

        cout << "\n=== Sign Up ===\n";
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Enter Password: ";
        getline(cin, password);
        clearScreen();

        ofstream file(FILENAME, ios::app);
        file << username << DELIMITER << email << DELIMITER << password << endl;
        file.close();

        cout << "\nAccount Created Successfully!\n";
        system("pause");
    }

    bool login() {
        clearScreen();
        cout << "\n=== Login ===\n";
        
        string inputUsername, inputPassword;
        cout << "\nEnter Username: ";
        getline(cin, inputUsername);
        clearScreen();
        
        cout << "\n=== Login ===\n";
        cout << "Username: " << inputUsername << endl;
        cout << "Enter Password: ";
        getline(cin, inputPassword);
        clearScreen();

        ifstream file(FILENAME);
        string line;
        
        while (getline(file, line)) {
            size_t pos1 = line.find(DELIMITER);
            size_t pos2 = line.find(DELIMITER, pos1 + 1);
            
            string fileUsername = line.substr(0, pos1);
            string filePassword = line.substr(pos2 + 1);
            
            if (fileUsername == inputUsername && filePassword == inputPassword) {
                cout << "\nLogin Successful!\n";
                file.close();
                system("pause");
                return true;
            }
        }
        
        file.close();
        cout << "\nLogin Failed! Incorrect Username or Password.\n";
        system("pause");
        return false;
    }

    bool forgotPassword() {
        clearScreen();
        cout << "\n=== Forgot Password ===\n";
        
        string inputUsername, inputEmail;
        cout << "\nEnter Username: ";
        getline(cin, inputUsername);
        clearScreen();
        
        cout << "\n=== Forgot Password ===\n";
        cout << "Username: " << inputUsername << endl;
        cout << "Enter Email: ";
        getline(cin, inputEmail);
        clearScreen();

        ifstream file(FILENAME);
        string line;
        
        while (getline(file, line)) {
            size_t pos1 = line.find(DELIMITER);
            size_t pos2 = line.find(DELIMITER, pos1 + 1);
            
            string fileUsername = line.substr(0, pos1);
            string fileEmail = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string filePassword = line.substr(pos2 + 1);
            
            if (fileUsername == inputUsername && fileEmail == inputEmail) {
                cout << "\nAccount Found!\n";
                cout << "Your Password: " << filePassword << endl;
                file.close();
                system("pause");
                return true;
            }
        }
        
        file.close();
        cout << "\nAccount Not Found!\n";
        system("pause");
        return false;
    }
};

int main() {
    char choice;
    User user;

    do {
        clearScreen();
        cout << "\n=== Menu ===\n"
             << "1. Login\n"
             << "2. Sign Up\n"
             << "3. Forgot Password\n"
             << "4. Exit\n"
             << "Enter Choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();

        switch (choice) {
            case '1':
                if (user.login()) {
                    cout << "Welcome to Your Profile!\n";
                }
                break;
            case '2':
                user.signUp();
                break;
            case '3':
                user.forgotPassword();
                break;
            case '4':
                cout << "\nGoodbye!\n";
                system("pause");
                break;
            default:
                cout << "\nInvalid Choice!\n";
                system("pause");
        }
    } while (choice != '4');

    return 0;
}
